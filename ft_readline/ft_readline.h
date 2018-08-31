/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:15:13 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/31 13:56:32 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <libft.h>

# include <termios.h>
# include <termcap.h>

enum		e_keys
{
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_CUT,
	KEY_COPY,
	KEY_PASTE,
	KEY_CTRL_LEFT,
	KEY_CTRL_RIGHT,
	KEY_CTRL_UP,
	KEY_CTRL_DOWN,
	KEY_BACKSPACE,
	KEY_DELETE,
	KEY_ENTER,
	KEY_COUNT
};

const char	*ft_readline(const char *prompt);

#endif
