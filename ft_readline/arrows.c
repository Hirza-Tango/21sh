/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 16:25:17 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/05 17:24:57 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	arrow_up(t_d_list **history, const char *prompt, size_t *pos)
{
	if ((*history)->next)
	{
		*history = (*history)->next;
		nav_home(prompt_len(prompt), pos);
		tputs(tgetstr("cr", NULL), 1, ft_putint);
		tputs(tgetstr("cd", NULL), 1, ft_putint);
		ft_putstr(prompt);
		ft_putstr((*history)->content);
		*pos = ft_strlen((*history)->content);
		return (1);
	}
	return (0);
}

int	arrow_down(t_d_list **history, const char *prompt, size_t *pos)
{
	if ((*history)->prev)
	{
		*history = (*history)->prev;
		nav_home(prompt_len(prompt), pos);
		tputs(tgetstr("cr", NULL), 1, ft_putint);
		tputs(tgetstr("cd", NULL), 1, ft_putint);
		ft_putstr(prompt);
		ft_putstr((*history)->content);
		*pos = ft_strlen((*history)->content);
		return (1);
	}
	return (0);
}

/*
**	TODO: multiline
*/

int	arrow_left(size_t prompt_len, size_t *pos)
{
	int	i;

	if (*pos)
	{
		if ((prompt_len + *pos) % tgetnum("co") == 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putint);
			i = 0;
			while (i++ < tgetnum("co") - 1)
				tputs(tgetstr("nd", NULL), 1, ft_putint);
		}
		else
			tputs(tgetstr("le", NULL), 1, ft_putint);
		(*pos)--;
		return (1);
	}
	return (0);
}

int	arrow_right(size_t prompt_len, size_t *pos, char *content)
{
	(void)prompt_len;
	if (content && *pos < ft_strlen(content))
	{
		if ((prompt_len + *pos + 1) % tgetnum("co") == 0)
		{
			tputs(tgetstr("do", NULL), 1, ft_putint);
			tputs("\r", 1, ft_putint);
		}
		else
			tputs(tgetstr("nd", NULL), 1, ft_putint);
		(*pos)++;
		return (1);
	}
	return (0);
}
