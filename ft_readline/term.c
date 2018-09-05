/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:11:22 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/05 18:12:05 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		set_term_raw(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	g_term = term;
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_oflag &= ~OPOST;
	tcsetattr(0, TCSAFLUSH, &term);
}

void		unset_term_raw(void)
{
	tcsetattr(0, TCSAFLUSH, &g_term);
}
