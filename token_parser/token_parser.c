/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:56:48 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/11 18:52:07 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"

t_list	*ft_lstfakenew(void *content, size_t content_size)
{
	t_list	*ret;

	ret = malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->content = content;
	ret->content_size = content_size;
	ret->next = NULL;
	return (ret);
}

int		ft_isop(char s)
{
	if (s == '|' || s == '&' || s == ';' || s == '<' || s == '>')
		return (1);
	return (0);
}

void	tok_newline(char **s, t_list **list)
{
	ft_lstappend(list, ft_lstfakenew(ft_strndup(*s, 1), TOK_NEWLINE));
	*s += 1;
}

void	tok_dquote(char **s, t_list **list)
{
	size_t	i;

	if (**s != '\"')
		return ;
	i = 1;
	while ((*s)[i] != '\"' && (*s)[i - 1] != '\\')
	{
		if (!(*s)[i])
			ft_swapnfree((void **)s, ft_strmjoin(3, *s, "\n", ft_readline("> ")));
		i++;
	}
	ft_lstappend(list, ft_lstfakenew(ft_strndup(*s, i + 1), TOK_DQUOTE));
	ft_putstr("LOG: ");
	ft_putendl((*list)->content);
	*s += i + 1;
}

void	tok_squote(char **s, t_list **list)
{
	size_t	i;

	if (**s != '\'')
		return ;
	i = 1;
	while ((*s)[i] != '\'')
	{
		if (!(*s)[i])
			ft_swapnfree((void **)s, ft_strmjoin(3, *s, "\n", ft_readline("> ")));
		i++;
	}
	ft_lstappend(list, ft_lstfakenew(ft_strndup(*s, i + 1), TOK_SQUOTE));
	*s += i + 1;
}

void	tok_word(char **s, t_list **list)
{
	char	*dup;
	char	prev;

	dup = *s;
	prev = 0;
	while (*dup)
	{
		if ((*dup == '\"' || *dup == '\'') && prev != '\\')
			break ;
		if (ft_isop(*dup) || ft_isspace(*dup))
			break ;
		if (*dup == '$' || *dup == '`' || *dup == '#')
			break ;
		prev = *dup;
		dup++;
	}
	ft_lstappend(list, ft_lstfakenew(ft_strndup(*s, dup - *s), TOK_WORD));
	(void)list;
	*s = dup;
}

t_list	*split_tokens(char *result)
{
	t_list	*list;

	list = NULL;
	while (*result)
	{
		if (*result == '\"')
			tok_dquote(&result, &list);
		else if (*result == '\'')
			tok_squote(&result, &list);
		//else if (ft_isop(*result))
		//	tok_operator(&result, &list);
		else if (*result == '\n')
			tok_newline(&result, &list);
		else if (ft_isspace(*result))
			result++;
		//else if (*result == '$' || *result == '`')
		//	tok_subst(&result, &list);
		//else if (*result == '#')
		//	tok_comment(&result, &list);
		else
			tok_word(&result, &list);
	}
	return (list);
}

char	quote_check(const char *s)
{
	char	*dup;

	dup = (char *)s;
	while (dup && *dup)
	{
		if (*dup == '\\')
		{
			if (dup[1])
				dup++;
			else
				return ('\\');
		}
		else if (*dup == '\'' && !(dup = ft_strchr(dup + 1, '\'')))
			return ('\'');
		else if (*dup == '\"')
		{
			while ((dup = ft_strchr(dup + 1, '\"')) && *(dup - 1) == '\\')
				PASS;
			if (!dup)
				return ('\"');
		}
		dup++;
	}
	return (0);
}

char	*token_list(const char *prompt)
{
	char	*result;
	t_list	*split;

	result = ft_readline(prompt);
	split = split_tokens(result);
	return (result);
}
