/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:48:05 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/26 11:46:45 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_shell_parser.h>

char	*continue_dquote(char **s, size_t *pos)
{
	(*pos)++;
	while ((*s)[(*pos)] != '\"' || (*s)[(*pos) - 1] == '\\')
	{
		if (!(*s)[(*pos)])
			ft_swapnfree((void **)s,
				ft_strmjoin(3, *s, "\n", ft_readline("DQUOTE: ")));
		(*pos)++;
	}
	return (*s);
}

char	*continue_squote(char **s, size_t *pos)
{
	(*pos)++;
	while ((*s)[(*pos)] != '\'')
	{
		if (!(*s)[(*pos)])
			ft_swapnfree((void **)s,
				ft_strmjoin(3, *s, "\n", ft_readline("SQUOTE: ")));
		(*pos)++;
	}
	return (*s);
}

char	*ft_get_full_line(const char *prompt)
{
	char	*result;
	size_t	i;

	result = ft_readline(prompt);
	i = -1;
	while (result[++i])
	{
		if (result[i] == '\"')
			continue_dquote(&result, &i);
		else if (result[i] == '\'')
			continue_squote(&result, &i);
		else if (result[i] == '\\')
			if (!result[++i])
				ft_swapnfree((void **)&result, ft_strmjoin(3, result, "\n",
					ft_readline("ESCAPE: ")));
	}
	return (result);
}

char	*strip_lit_newline(char *s)
{
	char	*ret;
	char	*dup;

	ret = malloc(ft_strlen(s) + 1);
	dup = ret;
	while (*s)
	{
		if (*s == '\\' && s[1] == '\n')
			s += 2;
		else
			*(dup++) = *(s++);
	}
	if (s[-1] == '\\')
		dup--;
	*dup = 0;
	return (ret);
}

char	*token_list(const char *prompt)
{
	char	*result;

	result = ft_get_full_line(prompt);
	ft_swapnfree((void **)&result, strip_lit_newline(result));
	ft_putendl(result);
	return (ft_strdup(result));
}
