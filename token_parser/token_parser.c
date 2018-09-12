/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:56:48 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/12 14:53:04 by dslogrov         ###   ########.fr       */
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

void	tok_operator(char **s, t_list **list)
{
	if (ft_is_redir_word(*s))
	{
		ft_lstappend(list, ft_lstfakenew(
			ft_strndup(*s, ft_is_redir_word(*s)), redir_type(*s)));
		*s += ft_is_redir_word(*s);
	}
	else if ((**s == '|' || **s == '&' || **s == ';') && (*s)[0] == (*s)[1])
	{
		if (**s == '|')
			ft_lstappend(list, ft_lstfakenew(ft_strndup((*s)++, 2), T_OR_IF));
		else if (**s == '&')
			ft_lstappend(list, ft_lstfakenew(ft_strndup((*s)++, 2), T_AND_IF));
		else if (**s == ';')
			ft_lstappend(list, ft_lstfakenew(ft_strndup((*s)++, 2), T_DSEMI));
		(*s)++;
	}
	else if (**s == '|')
		ft_lstappend(list, ft_lstfakenew(ft_strndup((*s)++, 1), T_PIPE));
	else if (**s == '&')
		ft_lstappend(list, ft_lstfakenew(ft_strndup((*s)++, 1), T_AMP));
	else if (**s == ';')
		ft_lstappend(list, ft_lstfakenew(ft_strndup((*s)++, 1), T_SEMI));
}

int		ft_is_op_char(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	tok_newline(char **s, t_list **list)
{
	ft_lstappend(list, ft_lstfakenew(ft_strndup(*s, 1), T_NEWLINE));
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
			ft_swapnfree((void **)s,
				ft_strmjoin(3, *s, "\n", ft_readline("> ")));
		i++;
	}
	ft_lstappend(list, ft_lstfakenew(ft_strndup(*s, i + 1), T_DQUOTE));
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
			ft_swapnfree((void **)s,
				ft_strmjoin(3, *s, "\n", ft_readline("> ")));
		i++;
	}
	ft_lstappend(list, ft_lstfakenew(ft_strndup(*s, i + 1), T_SQUOTE));
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
		if (ft_is_op_char(*dup) || ft_isspace(*dup))
			break ;
		if (*dup == '$' || *dup == '`' || *dup == '#')
			break ;
		prev = *dup;
		dup++;
	}
	ft_lstappend(list, ft_lstfakenew(ft_strndup(*s, dup - *s), T_WORD));
	(void)list;
	*s = dup;
}

void	tok_space(char **s, t_list **list)
{
	while (ft_isspace(**s) && **s != '\n')
		(*s)++;
	ft_lstappend(list, ft_lstfakenew(ft_strdup(" "), T_SPACE));
}

void	tok_comment(char **s, t_list **list)
{
	char *dup;

	if (**s != '#')
		return ;
	dup = *s + 1;
	while (*dup != '\n' && *dup)
		dup++;
	ft_lstappend(list, ft_lstfakenew(ft_strndup(*s, dup - *s), T_COMMENT));
	*s = dup;
}

t_list	*split_tokens(char *result)
{
	t_list	*list;
	char	*dup;

	list = NULL;
	dup = result;
	while (*dup)
	{
		if (*dup == '\"')
			tok_dquote(&dup, &list);
		else if (*dup == '\'')
			tok_squote(&dup, &list);
		else if (ft_is_op_char(*dup) || ft_is_redir_word(dup))
			tok_operator(&dup, &list);
		else if (*dup == '\n')
			tok_newline(&dup, &list);
		else if (ft_isspace(*dup))
			tok_space(&dup, &list);
		//else if (*dup == '$' || *dup == '`')
		//	tok_subst(&dup, &list);
		else if (*dup == '#')
			tok_comment(&dup, &list);
		else
			tok_word(&dup, &list);
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
			/*ft_putstr("SPACE");*/ break;
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
