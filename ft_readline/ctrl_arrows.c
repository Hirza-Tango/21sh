/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 10:59:21 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/05 18:35:51 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		ctrl_arrow_up(size_t prompt_len, size_t *pos)
{
	if (*pos)
	{
		if (*pos < (unsigned)tgetnum("co"))
			nav_home(prompt_len, pos);
		else
		{
			tputs(tgetstr("up", NULL), 1, ft_putint);
			*pos -= tgetnum("co");
		}
		return (1);
	}
	return (0);
}

int		ctrl_arrow_down(size_t prompt_len, size_t *pos, char *content)
{
	if (*pos < ft_strlen(content))
	{
		if (*pos + tgetnum("co") > ft_strlen(content))
			nav_end(prompt_len, pos, content);
		else
		{
			tputs(tgetstr("do", NULL), 1, ft_putint);
			*pos += tgetnum("co");
		}
		return (1);
	}
	return (0);
}

int		ctrl_arrow_left(size_t prompt_len, size_t *pos, char *content)
{
	while (*pos && ft_isspace(content[*pos - 1]) && arrow_left(prompt_len, pos))
		PASS;
	while (*pos && !ft_isspace(content[*pos - 1]) &&
		arrow_left(prompt_len, pos))
		PASS;
	return (1);
}

int		ctrl_arrow_right(size_t prompt_len, size_t *pos, char *content)
{
	while (*pos <= ft_strlen(content) && ft_isspace(content[*pos]) &&
		arrow_right(prompt_len, pos, content))
		PASS;
	while (*pos <= ft_strlen(content) && !ft_isspace(content[*pos]) &&
		arrow_right(prompt_len, pos, content))
		PASS;
	return (1);
}
