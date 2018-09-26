/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 13:57:44 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/26 17:13:44 by dslogrov         ###   ########.fr       */
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
	(*pos)++;
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
	(*pos)++;
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
