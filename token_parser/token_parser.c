/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:56:48 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/13 13:14:21 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"

t_list	*ft_lstfake(void *content, size_t content_size)
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

int		redir_type(char *s)
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

int		ft_is_redir_word(char *s)
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

void	tok_operator(char *s, t_list **list, size_t *i)
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

int		ft_is_op_char(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	tok_newline(char *s, t_list **list, size_t *i)
{
	ft_lstappend(list, ft_lstfake(ft_strsub(s, (*i)++, 1), T_NEWLINE));
}

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
		if (/*s[j] == '$' || s[j] == '`' || */s[j] == '#')
			break ;
		prev = s[j];
		j++;
	}
	ft_lstappend(list, ft_lstfake(ft_strsub(s, *i, j - *i), T_WORD));
	*i = j;
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
		//else if (*result == '$' || *result == '`')
		//	tok_subst(&result, &list);
		else if (result[i] == '#')
			tok_comment(result, &list, &i);
		else
			tok_word(result, &list, &i);
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

char	*token_list(const char *prompt)
{
	char	*result;
	t_list	*split;

	result = ft_readline(prompt);
	split = split_tokens(result);
	ft_lstiter(split, list_print);
	ft_putendl("LOG: Done parsing");
	return (ft_strdup(""));
}
