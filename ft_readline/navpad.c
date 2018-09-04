/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navpad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 10:58:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/04 12:37:47 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	nav_backspace(size_t *pos, char *content)
{
	const size_t	end = ft_strlen(content);

	if (!*pos)
		return (0);
	tputs(tgetstr("le", NULL), 1, ft_putint);
	(*pos)--;
	ft_memmove(content + *pos, content + *pos + 1, end - *pos);
	content[end - 1] = 0;
	tputs(tgetstr("dc", NULL), 1, ft_putint);
	return (1);
}

int	nav_delete(size_t *pos, char *content)
{
	const size_t	end = ft_strlen(content);

	if (end == *pos)
		return (0);
	ft_memmove(content + *pos, content + *pos + 1, end - *pos);
	content[end - 1] = 0;
	tputs(tgetstr("dc", NULL), 1, ft_putint);
	return (1);
}

int	nav_home(size_t prompt_len, size_t *pos)
{
	while (arrow_left(prompt_len, pos))
		PASS;
	return (1);
}

int	nav_end(size_t prompt_len, size_t *pos, char *content)
{
	while (arrow_right(prompt_len, pos, content))
		PASS;
	return (1);
}
