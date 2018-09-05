/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:15:13 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/05 16:13:31 by dslogrov         ###   ########.fr       */
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
	KEY_LEFT = 4479771,
	KEY_RIGHT = 4414235,
	KEY_UP = 4283163,
	KEY_DOWN = 4348699,
	KEY_CUT = 'x' | 0x0200,
	KEY_COPY = 'c' | 0x0200,
	KEY_PASTE = 'v' | 0x0200,
	KEY_CTRL_LEFT = 74995417045787,
	KEY_CTRL_RIGHT = 73895905418011,
	KEY_CTRL_UP = 71696882162459,
	KEY_CTRL_DOWN = 72796393790235,
	KEY_BACKSPACE = 127,
	KEY_DELETE = 2117294875,
	KEY_ENTER = '\n',
	KEY_HOME = 4741915,
	KEY_END = 4610843,
	KEY_COUNT
};

const char	*ft_readline(const char *prompt);
int			insert_char(t_d_list *entry, int c, const char *prompt, size_t *pos);
int			ft_putint(int c);
size_t		prompt_len(const char *prompt);

int			arrow_up(t_d_list **history, const char *prompt, size_t *pos);
int			arrow_down(t_d_list **history, const char *prompt, size_t *pos);
int			arrow_left(size_t prompt_len, size_t *pos);
int			arrow_right(size_t prompt_len, size_t *pos, char *content);

int			ctrl_arrow_left(size_t prompt_len, size_t *pos, char *content);
int			ctrl_arrow_right(size_t prompt_len, size_t *pos, char *content);

int			nav_end(size_t prompt_len, size_t *pos, char *content);
int			nav_home(size_t prompt_len, size_t *pos);
int			nav_delete(size_t *pos, char *content);
int			nav_backspace(size_t *pos, char *content);

#endif
