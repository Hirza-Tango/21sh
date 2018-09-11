/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:56:48 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/11 11:33:53 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"

/*char	*token_recognise(char **input)
{
	PASS;
}*/

char	quote_check(const char *s)
{
	char	*dup;

	dup = (char *)s;
	while (dup && *dup)
	{
		if (*dup == '\\')
			dup[1] ? dup++ : PASS;
		else if (*dup == '\'')
		{
			if (!(dup = ft_strchr(dup + 1, '\'')))
				return ('\'');
		}
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
	char		*result;
	//char		*token;
	t_d_list	*list;

	result = ft_readline(prompt);
	while (quote_check(result))
	{
		ft_swapnfree((void **)&result,
		ft_strmjoin(3, result, "\n", ft_readline("> ")));
	}
	list = NULL;
	//while ((token = token_recognise(result)))
	//	ft_dlstadd(&list, ft_dlstnew(token, TOK_TOKEN));
	return (result);
}
