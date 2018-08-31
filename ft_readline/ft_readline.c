/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:13:32 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/31 16:09:25 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

int			ft_putint(int c)
{
	char	ch;

	ch = c;
	write(1, &ch, 1);
	return (c);
}

static long	*init_keys(void)
{
	long	*tab;

	tab = (long *)ft_memalloc(sizeof(long) * KEY_COUNT);
	tgetstr("kl", (char **)&tab[KEY_LEFT]);
	tgetstr("kr", (char **)&tab[KEY_RIGHT]);
	tgetstr("ku", (char **)&tab[KEY_UP]);
	tgetstr("kd", (char **)&tab[KEY_DOWN]);
	tab[KEY_CUT] = 'x' | 0x0200;
	tab[KEY_COPY] = 'c' | 0x0200;
	tab[KEY_PASTE] = 'v' | 0x0200;
	tab[KEY_CTRL_LEFT] = tab[KEY_LEFT] | 0x0200;
	tab[KEY_CTRL_RIGHT] = tab[KEY_RIGHT] | 0x0200;
	tab[KEY_CTRL_UP] = tab[KEY_UP] | 0x0200;
	tab[KEY_CTRL_DOWN] = tab[KEY_DOWN] | 0x0200;
	tgetstr("kb", (char **)&tab[KEY_BACKSPACE]);
	tgetstr("kD", (char **)&tab[KEY_DELETE]);
	tab[KEY_ENTER] = '\n';
	return (tab);
}

static void	meta_key_handler(long key, t_d_list *history, long *keys)
{
	if (key == keys[KEY_COPY])
		PASS;
	else if (key == keys[KEY_CUT])
		PASS;
	else if (key == keys[KEY_PASTE])
		PASS;
	else if (key == keys[KEY_CTRL_UP])
		PASS;
	else if (key == keys[KEY_CTRL_DOWN])
		PASS;
	else if (key == keys[KEY_CTRL_LEFT])
		PASS;
	else if (key == keys[KEY_CTRL_RIGHT])
		PASS;
}

static void	raw_key_handler(long key, t_d_list *history, long *keys)
{
	if (ft_isprint(key))
		PASS;
	//"ic" capability can be used to insert character
	else if (key == keys[KEY_UP])
		PASS;
	else if (key == keys[KEY_DOWN])
		PASS;
	else if (key == keys[KEY_LEFT])
		PASS;
	//tputs("le", 1, ft_putint);
	else if (key == keys[KEY_RIGHT])
		PASS;
	else if (key == keys[KEY_BACKSPACE])
		PASS;
	else if (key == keys[KEY_DELETE])
		PASS;
	else if (key == keys[KEY_ENTER])
		PASS;
	else if (key & 0x0200)
		meta_key_handler(key, history, keys);
}

void		set_term_raw(void)
{
	struct termios	term;

	tcgetattr(2, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_oflag &= ~OPOST;
	tcsetattr(2, TCSAFLUSH, &term);
}

const char	*ft_readline(const char *prompt)
{
	t_d_list		*dup;
	static long		*keys = NULL;
	static t_d_list	*list = NULL;
	long			key;

	if (!keys)
		keys = init_keys();
	ft_dlstadd(&list, ft_dlstnew(NULL, 0));
	while (1)
	{
		key = 0;
		read(0, &key, sizeof(long));
		raw_key_handler(key, list, keys);
	}
	return ((const char *)list->content);
}
