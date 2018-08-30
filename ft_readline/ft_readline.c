/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:13:32 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/30 13:13:08 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

int		ft_putint(int c)
{
	write(1, c, sizeof(c));
}

static long	*init_keys(void)
{
	long	*tab;

	tab = ft_memalloc(KEY_COUNT * sizeof(long));
	tgetstr("kl", &tab[KEY_LEFT]);
	tgetstr("kr", &tab[KEY_RIGHT]);
	tgetstr("ku", &tab[KEY_UP]);
	tgetstr("kd", &tab[KEY_DOWN]);
	tab[KEY_CUT] = L'x' & 0x0200;
	tab[KEY_COPY] = L'c' & 0x0200;
	tab[KEY_PASTE] = L'v' & 0x0200;
	tab[KEY_CTRL_LEFT] = tab[KEY_LEFT] & 0x0200;
	tab[KEY_CTRL_RIGHT] = tab[KEY_RIGHT] & 0x0200;
	tab[KEY_CTRL_UP] = tab[KEY_UP] & 0x0200;
	tab[KEY_CTRL_DOWN] = tab[KEY_DOWN] & 0x0200;
	tgetstr("kb", &tab[KEY_BACKSPACE]);
	tgetstr("kD", &tab[KEY_DELETE]);
	tab[KEY_ENTER] = '\n';
	return (tab);
}

static void	raw_key_handler(char *key, char *buffer)
{
	//change to handle 4 byte buffer
	if (ft_isprint(key))
	{
		ft_putchar(key);
		//check if buffer is big enough
		buffer[ft_strlen(buffer)] = key;
		//"ic" capability can be used to insert character
		//replace with better position
	}
	else if (key == KEY_DELETE)
		buffer[ft_strlen(buffer - 1)] = 0;
	else if (key == KEY_LEFT)
		tputs("le", 1, ft_putint);
}

char	*ft_readline(const char *prompt)
{
	t_d_list		*dup;
	struct termios	term;
	static char		**keys = NULL;
	long			key;
	
	if (!keys)
		keys = init_keys();
	tcgetattr(2, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_oflag &= ~OPOST;
	tcsetattr(2, TCSAFLUSH, &term);
	key = 0;
	while (1)
	{
		read(0, key, sizeof(long));
		raw_key_handler(key, NULL);
		key = 0;
	}
	return ;
}