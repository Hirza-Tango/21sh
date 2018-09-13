/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 15:43:48 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/13 17:21:45 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"

void	tok_dquote(char **s, t_list **list, size_t *i)
{
	size_t	j;

	j = ++(*i);
	while ((*s)[j] != '\"' && (*s)[j - 1] != '\\')
	{
		if (!(*s)[j])
			ft_swapnfree((void **)s,
				ft_strmjoin(3, *s, "\n", ft_readline("DQUOTE: ")));
		j++;
	}
	ft_lstappend(list, ft_lstfake(ft_strsub(*s, *i, j - *i), T_DQUOTE));
	*i = j + 1;
}

void	tok_squote(char **s, t_list **list, size_t *i)
{
	size_t	j;

	j = ++(*i);
	while ((*s)[j] != '\'')
	{
		if (!(*s)[j])
			ft_swapnfree((void **)s,
				ft_strmjoin(3, *s, "\n", ft_readline("SQUOTE: ")));
		j++;
	}
	ft_lstappend(list, ft_lstfake(ft_strsub(*s, *i, j - *i), T_SQUOTE));
	*i = j + 1;
}

void	tok_word(char *s, t_list **list, size_t *i)
{
	char	prev;
	size_t	j;

	j = *i;
	prev = 0;
	while (s[j])
	{
		if ((s[j] == '\"' || s[j] == '\'') && prev != '\\')
			break ;
		//TODO: line continuation on '//'
		if (ft_is_op_char(s[j]) || ft_isspace(s[j]))
			break ;
		/*if (s[j] == '`')
			break ;*/
		prev = s[j];
		j++;
	}
	ft_lstappend(list, ft_lstfake(ft_strsub(s, *i, j - *i), T_WORD));
	*i = j;
}
