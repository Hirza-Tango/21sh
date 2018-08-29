/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:13:32 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/29 16:34:18 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

static char	**init_keys(void)
{
	char **tab;

	tab = malloc(KEY_COUNT * sizeof(char *));
	tab[KEY_LEFT] = tgetstr("kl", NULL);
	tab[KEY_RIGHT] = tgetstr("kr", NULL);
	tab[KEY_UP] = tgetstr("ku", NULL);
	tab[KEY_DOWN] = tgetstr("kd", NULL);
	tab[KEY_CUT] = ft_strdup("");//TODO: CTRL bindings
	tab[KEY_COPY] = tgetstr("", NULL);
	tab[KEY_PASTE] = tgetstr("", NULL);
	tab[KEY_CTRL_LEFT] = tgetstr("", NULL);
	tab[KEY_CTRL_RIGHT] = tgetstr("", NULL);
	tab[KEY_CTRL_UP] = tgetstr("", NULL);
	tab[KEY_CTRL_DOWN] = tgetstr("", NULL);
	tab[KEY_BACKSPACE] = tgetstr("kb", NULL);
	tab[KEY_DELETE] = tgetstr("kD", NULL);
	tab[KEY_ENTER] = ft_strdup("\n");
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
		tputs("le", 1, putchar);
}

char	*ft_readline(const char *prompt)
{
	t_d_list		*dup;
	struct termios	term;
	static char		**keys = NULL;
	char			*key;
	
	if (!keys)
		keys = init_keys();
	tcgetattr(2, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_oflag &= ~OPOST;
	tcsetattr(2, TCSAFLUSH, &term);
	ft_bzero(key, 4);
	while (1)
	{
		read(0, key, sizeof(long));
		raw_key_handler(key, NULL);
		ft_bzero(key, 4);
	}
	return ;
}