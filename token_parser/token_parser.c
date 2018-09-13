/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:56:48 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/13 17:25:46 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"

t_list	*split_tokens(char *result)
{
	t_list	*list;
	size_t	i;

	list = NULL;
	i = 0;
	while (result[i])
	{
		if (result[i] == '\"')
			tok_dquote(&result, &list, &i);
		else if (result[i] == '\'')
			tok_squote(&result, &list, &i);
		else if (ft_is_op_char(result[i]) || ft_is_redir_word(result + i))
			tok_operator(result, &list, &i);
		else if (result[i] == '\n')
			tok_newline(result, &list, &i);
		else if (ft_isspace(result[i]))
			tok_space(result, &list, &i);
		//else if (*result == '$' /*|| *result == '`'*/)
		//	tok_subst(&result, &list, &i);
		else if (result[i] == '#')
			tok_comment(result, &list, &i);
		else
			tok_word(result, &list, &i);
	}
	return (list);
}

void	list_print(t_list *elem)
{
	ft_putstr("LOG: TYPE: ");
	switch (elem->content_size)
	{
		case T_WORD :
			ft_putstr("WORD"); break;
		case T_DQUOTE :
			ft_putstr("DQUOTE"); break;
		case T_SQUOTE :
			ft_putstr("SQUOTE"); break;
		case T_NEWLINE :
			ft_putstr("NEWLINE"); break;
		case T_SPACE :
			break;
		case T_COMMENT :
			ft_putstr("COMMENT"); break;
		default :
			ft_putstr("OTHER");
	}
	ft_putstr(" CONTENT: ");
	ft_putendl(elem->content);
}

void	subst(t_list *elem)
{
	const size_t	type = elem->content_size;
	char			*s;
	size_t			i;
	char			*new;

	if (type != T_WORD && type != T_DQUOTE)
		return ;
	if (*((char *)elem->content) == '~')
		ft_swapnfree((void **)&elem->content,
			abs_to_rel(elem->content, g_env, 1));
	i = 0;
	s = (char *)elem->content;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] != '?' && s[i + 1] != '@')
		{
			new = ft_strnew(i + ft_strlen(ft_getenv(s + i + 1, g_env)) + 1);
			ft_strncat(new, s, i);
			ft_strcat(new, ft_getenv(s + i + 1, g_env));
			ft_swapnfree((void **)&elem->content, new);
			break ;
		}
		i++;
	}
}

char	*token_list(const char *prompt)
{
	char	*result;
	t_list	*split;

	result = ft_readline(prompt);
	split = split_tokens(result);

	//ft_putendl(result);
	ft_lstiter(split, subst);
	ft_lstiter(split, list_print);
	//ft_putendl("LOG: Done parsing");
	return (ft_strdup(""));
}
