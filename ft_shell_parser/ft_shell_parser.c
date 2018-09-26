/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:48:05 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/26 17:39:48 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_shell_parser.h>

void	add_token(t_token **list, char *token, int type)
{
	t_token	*new;
	t_token *dup;

	ft_putstr("Adding token: ");
	ft_putstr(token);
	ft_putstr(" of type: ");
	ft_putnbr(type);
	ft_putstr(" and length: ");
	ft_putnbr(ft_strlen(token));
	ft_putendl("");
	if (*token == ' ' || !*token)
		return ;
	new = malloc(sizeof(t_token));
	new->token = token;
	new->type = type;
	new->next = NULL;
	dup = *list;
	if (dup)
	{
		while (dup->next)
			dup = dup->next;
		dup->next = new;
	}
	else
		*list = new;
}

char	*delim(char *s, size_t *start, size_t *end)
{
	char *token;

	token = ft_strsub(s, *start, *end - *start);
	*start = ++(*end);
	return (token);
}

int		is_op_tok(char *s, size_t end)
{
	(void)(s && end);
	return (0);
}

int		is_op_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == ';');
}

t_token	*tokenize(char *s)
{
	size_t	start;
	size_t	end;
	t_token	*lst;
	char	type;

	start = 0;
	end = 0;
	type = T_WORD;
	lst = NULL;
	while (s[end])
	{
		if (type == T_OPERATOR && !is_op_tok(s + start, end))
		{
			add_token(&lst, delim(s, &start, &end), type);
			start--;
			type = T_WORD;
		}
		else if (type == T_OPERATOR)
			end++;
		else if (s[end] == '\"')
			continue_dquote(&s, &end);
		else if (s[end] == '\'')
			continue_squote(&s, &end);
		else if (s[end] == '\\')
			continue_lit(&s, &end);
		//else if (s[end] == '`' || s[end] == '$')
		//	parameter_expand();
		else if (is_op_char(s[end]))
		{
			add_token(&lst, delim(s, &start, &end), type);
			start--;
			type = T_OPERATOR;
		}
		else if (s[end] == '\n')
			add_token(&lst, delim(s, &start, &end), type);
		else if (s[end] == ' ')//TODO: proper IFS
		{
			ft_putstr("SPACE: ");
			add_token(&lst, delim(s, &start, &end), type);
		}
		else if (type == T_WORD)
			end++;
		else if (s[end] == '#')
			end++;//goto EOL
		else
		{
			type = T_WORD;
			end++;
		}
	}
	ft_putendl("End");
	if (start == end)
		add_token(&lst, ft_strdup(""), T_EOF);
	else
		add_token(&lst, delim(s, &start, &end), type);
	return (lst);
}

char	*strip_lit_newline(char *s)
{
	char	*ret;
	char	*dup;

	ret = malloc(ft_strlen(s) + 1);
	dup = ret;
	while (*s)
	{
		if (*s == '\\' && s[1] == '\n')
			s += 2;
		else
			*(dup++) = *(s++);
	}
	if (s[-1] == '\\')
		dup--;
	*dup = 0;
	return (ret);
}

char	*token_list(const char *prompt)
{
	char	*result;
	t_token	*token_list;

	result = ft_readline(prompt);
	ft_swapnfree((void **)&result, strip_lit_newline(result));
	token_list = tokenize(result);
	while (token_list)
	{
		ft_putstr("TYPE: ");
		ft_putnbr(token_list->type);
		ft_putstr(" TOKEN: ");
		ft_putendl(token_list->token);
		token_list = token_list->next;
	}
	//ft_putendl(result);
	return (ft_strdup(result));
}
