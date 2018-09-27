/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:48:05 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/27 15:57:52 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_shell_parser.h>

void	add_token(t_token **list, char *token, int type)
{
	t_token	*new;
	t_token *dup;

	if (!*token)
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

char	*delim(char *s, size_t *start, size_t end)
{
	char *token;

	token = ft_strsub(s, *start, end - *start);
	*start = end;
	return (token);
}

int		op_tok(char *s, size_t start, size_t end)
{
	if (!ft_strncmp(s + start, "|", end - start))
		return (T_PIPE);
	if (!ft_strncmp(s + start, ";", end - start))
		return (T_SEMI);
	if (!ft_strncmp(s + start, "<", end - start))
		return (T_LESS);
	if (!ft_strncmp(s + start, ">", end - start))
		return (T_GREAT);
	if (!ft_strncmp(s + start, "||", end - start))
		return (T_OR_IF);
	if (!ft_strncmp(s + start, "&&", end - start))
		return (T_AND_IF);
	if (!ft_strncmp(s + start, "<<", end - start))
		return (T_DLESS);
	if (!ft_strncmp(s + start, ">>", end - start))
		return (T_DGREAT);
	if (!ft_strncmp(s + start, "<&", end - start))
		return (T_LESSAND);
	if (!ft_strncmp(s + start, ">&", end - start))
		return (T_GREATAND);
	if (!ft_strncmp(s + start, "<>", end - start))
		return (T_LESSGREAT);
	return (0);
}

int		is_op_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == ';');
}

t_token	*tokenize(char *s, char **env)
{
	size_t	start;
	size_t	end;
	t_token	*lst;
	char	type;

	start = 0;
	end = -1;
	type = T_WORD;
	lst = NULL;
	while (s[++end])
	{
		if (type == T_OPERATOR && !op_tok(s, start, end))
		{
			end--;
			add_token(&lst, delim(s, &start, end), op_tok(s, start, end));
			end--;
			type = T_WORD;
		}
		else if (type == T_OPERATOR)
			PASS;
		else if (s[end] == '\\')
			continue_lit(&s, &end);
		else if (s[end] == '\"')
			continue_dquote(&s, &end);
		else if (s[end] == '\'')
			continue_squote(&s, &end);
		else if (s[end] == '$' || s[end] == '`')
			continue_substitution(&s, &end, env);
		else if (is_op_char(s[end]))
		{
			add_token(&lst, delim(s, &start, end), type);
			type = T_OPERATOR;
		}
		else if (s[end] == '\n')
			add_token(&lst, delim(s, &start, end), type);
		else if (ft_isspace(s[end]))//TODO: IFS parsing
		{
			add_token(&lst, delim(s, &start, end), type);
			start++;
		}
		else
			type = T_WORD;
	}
	add_token(&lst, delim(s, &start, end), type);
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

char	*token_list(const char *prompt, char **env)
{
	char	*result;
	t_token	*token_list;

	result = ft_readline(prompt);
	ft_swapnfree((void **)&result, strip_lit_newline(result));
	token_list = tokenize(result, env);
	while (token_list)
	{
		ft_putstr("TYPE: ");
		ft_putnbr(token_list->type);
		ft_putstr(" TOKEN: ");
		ft_putendl(token_list->token);
		token_list = token_list->next;
	}
	return (ft_strdup(result));
}
