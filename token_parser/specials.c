/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 15:44:52 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/13 15:45:04 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"

void	tok_newline(char *s, t_list **list, size_t *i)
{
	ft_lstappend(list, ft_lstfake(ft_strsub(s, (*i)++, 1), T_NEWLINE));
}

void	tok_space(char *s, t_list **list, size_t *i)
{
	while (ft_isspace(s[*i]) && s[*i] != '\n')
		(*i)++;
	ft_lstappend(list, ft_lstfake(ft_strdup(" "), T_SPACE));
}

void	tok_comment(char *s, t_list **list, size_t *i)
{
	size_t	j;

	j = *i;
	while (s[j] != '\n' && s[j])
		j++;
	ft_lstappend(list, ft_lstfake(ft_strsub(s, *i, j - *i), T_COMMENT));
	*i = j;
}
