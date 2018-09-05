/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:13:32 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/05 16:32:58 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_d_list	*elem_cpy(t_d_list *elem)
{
	return (ft_dlstnew(elem->content, elem->content_size));
}

size_t		prompt_len(const char *prompt)
{
	char	*temp;
	size_t	ret;

	temp = (char *)prompt;
	ret = 0;
	while (*prompt)
	{
		if (*prompt == '\e')
			while (*prompt != 'm')
				prompt++;
		else
			ret++;
		prompt++;
	}
	return(ret);
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

int			meta_key_handler(long key, t_d_list **history, const char *prompt,
	size_t *pos)
{
	(void)history;
	if (key == KEY_COPY)
		PASS;
	else if (key == KEY_CUT)
		PASS;
	else if (key == KEY_PASTE)
		PASS;
	else if (key == KEY_CTRL_UP)
		PASS;
	else if (key == KEY_CTRL_DOWN)
		PASS;
	else if (key == KEY_CTRL_LEFT)
		ctrl_arrow_left(prompt_len(prompt), pos, (*history)->content);
	else if (key == KEY_CTRL_RIGHT)
		ctrl_arrow_right(prompt_len(prompt), pos, (*history)->content);
	else if (key == KEY_HOME)
		nav_home(prompt_len(prompt), pos);
	else if (key == KEY_END)
		nav_end(prompt_len(prompt), pos, ((*history)->content));
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
		insert_char(*history, key, prompt, pos);
	else if (key == KEY_UP)
		arrow_up(history, prompt, pos);
	else if (key == KEY_DOWN)
		arrow_down(history, prompt, pos);
	else if (key == KEY_LEFT)
		arrow_left(prompt_len(prompt), pos);
	else if (key == KEY_RIGHT)
		arrow_right(prompt_len(prompt), pos, (*history)->content);
	else if (key == KEY_BACKSPACE)
		nav_backspace(pos, (*history)->content);
	else if (key == KEY_DELETE)
		nav_delete(pos, (*history)->content);
	else if (key == KEY_ENTER)
	{
		nav_end(prompt_len(prompt), pos, (*history)->content);
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
