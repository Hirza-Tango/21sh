/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 10:55:51 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/05 16:30:02 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		ft_strinsert(char *str, char c, size_t pos)
{
	if (pos > ft_strlen(str))
		return (0);
	ft_memmove(str + pos + 1, str + pos, ft_strlen(str) - pos);
	str[pos] = c;
	return (1);
}

/*
**	TODO: inserting on an upper line needs to redraw
*/

int		insert_char(t_d_list *entry, int c, const char *prompt, size_t *pos)
{
	char	*new_buff;
	size_t	i;
	size_t	pos_dup;
	const size_t	prompt_sz = prompt_len(prompt);

	if (!*(char *)entry->content)
	{
		ft_swapnfree(&(entry->content),
			ft_memalloc(tgetnum("co") - prompt_sz + 1));
		entry->content_size = tgetnum("co") - prompt_sz + 1;
	}
	else if (entry->content_size == ft_strlen(entry->content) - 1)
	{
		new_buff = ft_memalloc(entry->content_size + tgetnum("co"));
		ft_strcpy(new_buff, entry->content);
		free(entry->content);
		entry->content = new_buff;
		entry->content_size += tgetnum("co");
	}
	entry->content_size += ft_strinsert(entry->content, c, (*pos)++);
	if ((*pos + prompt_sz) / tgetnum("co") ==
		(ft_strlen(entry->content) + prompt_sz) / tgetnum("co"))
	{
		tputs(tgetstr("im", NULL), 1, ft_putint);
		ft_putint(c);
		tputs(tgetstr("ei", NULL), 1, ft_putint);
	}
	else
	{
		i = ((ft_strlen(entry->content) + prompt_sz) / tgetnum("co")) -
			((*pos + prompt_sz) / tgetnum("co"));
		while (--i)
			tputs(tgetstr("up", NULL), 1, ft_putint);
		tputs("\r", 1, ft_putint);
		tputs(tgetstr("cd", NULL), 1, ft_putint);
		ft_putstr(prompt);
		ft_putstr(entry->content);
		pos_dup = ft_strlen(entry->content) + prompt_sz;
		while (pos_dup > *pos)
			arrow_left(prompt_sz, &pos_dup);
	}
	return (1);
}
