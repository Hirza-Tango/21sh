/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:15:13 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/04 15:19:48 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <libft.h>

# include <termios.h>
# include <termcap.h>

long			*g_keys;
struct termios	g_term;

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
	KEY_HOME,
	KEY_END,
	KEY_COUNT
};

const char	*ft_readline(const char *prompt);
int			insert_char(t_d_list *entry, int c, size_t prompt_length,
	size_t *pos);
int			ft_putint(int c);

int			arrow_up(t_d_list **history, const char *prompt, size_t *pos);
int			arrow_down(t_d_list **history, const char *prompt, size_t *pos);
int			arrow_left(size_t prompt_len, size_t *pos);
int			arrow_right(size_t prompt_len, size_t *pos, char *content);

int			nav_end(size_t prompt_len, size_t *pos, char *content);
int			nav_home(size_t prompt_len, size_t *pos);
int			nav_delete(size_t *pos, char *content);
int			nav_backspace(size_t *pos, char *content);

#endif
