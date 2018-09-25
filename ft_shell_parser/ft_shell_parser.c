/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:48:05 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/25 16:55:50 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_shell_parser.h>

char	*continue_dquote(char *s)
{
	size_t	i;

	i = 0;
	while (s[++i] != '\"' || s[i - 1] == '\\')
	if (!s[i])
		ft_swapnfree((void **)&result, ft_strmjoin(3, result, "\n",
			ft_readline("DQUOTE: ")));
}

char	*continue_squote(char *s)
{
	size_t	i;

	i = 0;
	while (s[++i] != '\'')
		if (!s[i])
			ft_swapnfree((void **)&result, ft_strmjoin(3, result, "\n",
				ft_readline("SQUOTE: ")));
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
			continue_dquote(&result[i])
		else if (result[i] == '\'')
			continue_squote(&result[i])
		else if (result[i] == '\\')
			if (!result[++i])
				ft_swapnfree((void **)&result, ft_strmjoin(3, result, "\n",
					ft_readline("ESCAPE: ")));
	}
	return (result);
}

char	*token_list(const char *prompt)
{
	char	*result;

	result = ft_get_full_line(prompt);
	ft_putendl(result);
	return (ft_strdup(result));
}
