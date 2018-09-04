/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:13:32 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/04 15:18:37 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_d_list	*elem_cpy(t_d_list *elem)
{
	return (ft_dlstnew(elem->content, elem->content_size));
}

void		elem_del(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

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

	tab = (long *)ft_memalloc(sizeof(long) * (KEY_COUNT));
	tab[KEY_LEFT] = 4479771;
	tab[KEY_RIGHT] = 4414235;
	tab[KEY_UP] = 4283163;
	tab[KEY_DOWN] = 4348699;
	//tab[KEY_CUT] = 'x' | 0x0200;
	//tab[KEY_COPY] = 'c' | 0x0200;
	//tab[KEY_PASTE] = 'v' | 0x0200;
	tab[KEY_CTRL_LEFT] = 74995417045787;
	tab[KEY_CTRL_RIGHT] = 73895905418011;
	tab[KEY_CTRL_UP] = 71696882162459;
	tab[KEY_CTRL_DOWN] = 72796393790235;
	tab[KEY_BACKSPACE] = 127;
	tab[KEY_DELETE] = 2117294875;
	tab[KEY_ENTER] = '\n';
	tab[KEY_HOME] = 4741915;
	tab[KEY_END] = 4610843;
	return (tab);
}

int			meta_key_handler(long key, t_d_list **history, const char *prompt,
	size_t *pos)
{
	(void)history;
	if (key == g_keys[KEY_COPY])
		PASS;
	else if (key == g_keys[KEY_CUT])
		PASS;
	else if (key == g_keys[KEY_PASTE])
		PASS;
	else if (key == g_keys[KEY_CTRL_UP])
		PASS;
	else if (key == g_keys[KEY_CTRL_DOWN])
		PASS;
	else if (key == g_keys[KEY_CTRL_LEFT])
		PASS;
	else if (key == g_keys[KEY_CTRL_RIGHT])
		PASS;
	else if (key == g_keys[KEY_HOME])
		nav_home(ft_strlen(prompt), pos);
	else if (key == g_keys[KEY_END])
		nav_end(ft_strlen(prompt), pos, ((*history)->content));
	else if (!key)
		return (0);
	return (1);
}

static int	raw_key_handler(long key, t_d_list **history, const char *prompt,
	size_t *pos)
{
	if (key == 4 && !*((char *)(*history)->content))
	{
		ft_putstr("exit\n\r");
		return (-1);
	}
	if (ft_isprint(key))
		insert_char(*history, key, ft_strlen(prompt), pos);
	else if (key == g_keys[KEY_UP])
		arrow_up(history, prompt, pos);
	else if (key == g_keys[KEY_DOWN])
		arrow_down(history, prompt, pos);
	else if (key == g_keys[KEY_LEFT])
		arrow_left(ft_strlen(prompt), pos);
	else if (key == g_keys[KEY_RIGHT])
		arrow_right(ft_strlen(prompt), pos, (*history)->content);
	else if (key == g_keys[KEY_BACKSPACE])
		nav_backspace(pos, (*history)->content);
	else if (key == g_keys[KEY_DELETE])
		nav_delete(pos, (*history)->content);
	else if (key == g_keys[KEY_ENTER])
	{
		ft_putstr("\n\r");
		return (0);
	}
	else
		return (meta_key_handler(key, history, prompt, pos));
	return (1);
}

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

const char	*ft_readline(const char *prompt)
{
	static t_d_list	*list = NULL;
	t_d_list		*dup;
	long			key;
	size_t			pos;

	if (!g_keys)
		g_keys = init_keys();
	dup = ft_dlstmap(list, elem_cpy);
	ft_dlstadd(&dup, ft_dlstnew("", 1));
	ft_putstr(prompt);
	set_term_raw();
	pos = 0;
	while (1)
	{
		key = 0;
		read(0, &key, sizeof(long));
		key = raw_key_handler(key, &dup, prompt, &pos);
		if (!key)
			break ;
		if (key < 0)
		{
			unset_term_raw();
			ft_dlstdel(&dup, elem_del);
			return (ft_strdup("exit"));
		}
	}
	unset_term_raw();
	if (!ft_strlen(dup->content))
	{
		ft_dlstdel(&dup, elem_del);
		return (ft_strdup(""));
	}
	ft_dlstadd(&list, elem_cpy(dup));
	ft_dlstdel(&dup, elem_del);
	return (ft_strdup(list->content));
}
