/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 13:57:44 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/27 14:46:47 by dslogrov         ###   ########.fr       */
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

char		*continue_lit(char **s, size_t *pos)
{
	(*pos)++;
	if (!(*s)[(*pos)++])
		ft_swapnfree((void **)s,
			ft_strmjoin(3, *s, "\n", ft_readline("ESCAPE: ")));
	return (*s);
}

/*
**	TODO: Parameter Expansion
**	TODO: Command substitution
**	TODO: Arithmetic expansion
*/

char		*continue_substitution(char **s, size_t *pos, char **env)
{
	size_t	end;
	char	*before;
	char	*after;
	char	*replace;
	char	*param;

	end = *pos + 1;
	if (ft_strnequ(*s + *pos, "$((", 3))
		(*pos)++;
	else if ((*s)[*pos] == '`' || ft_strnequ((*s) + *pos, "$(", 2))
		(*pos)++;
	else
	{
		if ((*s)[*pos + 1] == '{')
			(*pos)++;
		else
		{
			while (ft_isalnum((*s)[end]) || (*s)[end] == '-')
				end++;
			param = ft_strsub(*s, *pos, end - *pos);
			before = ft_strndup(*s, *pos);
			after = ft_strdup(*s + end);
			if (!(replace = ft_getenv(param + 1, env)))
				replace = "";
			ft_swapnfree((void **)s, ft_strmjoin(3, before, replace, after));
			free(param);
			free(before);
			free(after);
			*pos += ft_strlen(replace) - 1;
		}
	}
	return (*s);
}
