/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 16:25:17 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/03 17:00:16 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	arrow_up(t_d_list **history, const char *prompt, size_t *pos)
{
	if ((*history)->next)
	{
		*history = (*history)->next;
		tputs(tgetstr("cr", NULL), 1, ft_putint);
		tputs(tgetstr("ce", NULL), 1, ft_putint);
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
		tputs(tgetstr("cr", NULL), 1, ft_putint);
		tputs(tgetstr("ce", NULL), 1, ft_putint);
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
	(void)prompt_len;
	if (*pos)
	{
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
		tputs(tgetstr("nd", NULL), 1, ft_putint);
		(*pos)++;
		return (1);
	}
	return (0);
}