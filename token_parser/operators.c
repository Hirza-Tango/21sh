/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:44:40 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/13 14:47:33 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"

static int	redir_type(char *s)
{
	while (ft_isdigit(*s))
		s++;
	if (s[0] == '<')
	{
		if (s[1] == '<')
			return (s[2] == '-' ? T_DLESSDASH : T_DLESS);
		else if (s[1] == '&')
			return (T_LESSAND);
		else if (s[1] == '>')
			return (T_LESSGREAT);
		return (T_LESS);
	}
	else if (*s == '>')
	{
		if (s[1] == '>')
			return (T_DGREAT);
		else if (s[1] == '&')
			return (T_GREATAND);
		else if (s[1] == '|')
			return (T_CLOBBER);
		return (T_GREAT);
	}
	return (0);
}

int			ft_is_redir_word(char *s)
{
	char *dup;

	dup = s;
	while (ft_isdigit(*dup))
		dup++;
	if (*dup == '<')
	{
		dup++;
		if (*dup == '<' || *dup == '>' || *dup == '&')
		{
			if (*dup == '<' && dup[1] == '-')
				return (dup - s + 2);
			return (dup - s + 1);
		}
		return (dup - s);
	}
	else if (*dup == '>')
	{
		dup++;
		if (*dup == '|' || *dup == '>' || *dup == '&')
			return (dup - s + 1);
		return (dup - s);
	}
	return (0);
}

void		tok_operator(char *s, t_list **list, size_t *i)
{
	if (ft_is_redir_word(&s[*i]))
	{
		ft_lstappend(list, ft_lstfake(
			ft_strndup(&s[*i], ft_is_redir_word(&s[*i])), redir_type(&s[*i])));
		*i += ft_is_redir_word(&s[*i]);
	}
	else if (s[*i] == s[*i + 1])
	{
		if (s[*i] == '|')
			ft_lstappend(list, ft_lstfake(ft_strsub(s, (*i)++, 2), T_OR_IF));
		else if (s[*i] == '&')
			ft_lstappend(list, ft_lstfake(ft_strsub(s, (*i)++, 2), T_AND_IF));
		else if (s[*i] == ';')
			ft_lstappend(list, ft_lstfake(ft_strsub(s, (*i)++, 2), T_DSEMI));
		(*i)++;
	}
	else if (s[*i] == '|')
		ft_lstappend(list, ft_lstfake(ft_strsub(s, (*i)++, 1), T_PIPE));
	else if (s[*i] == '&')
		ft_lstappend(list, ft_lstfake(ft_strsub(s, (*i)++, 1), T_AMP));
	else if (s[*i] == ';')
		ft_lstappend(list, ft_lstfake(ft_strsub(s, (*i)++, 1), T_SEMI));
}

int			ft_is_op_char(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}
