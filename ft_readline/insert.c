/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 10:55:51 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/04 16:04:05 by dslogrov         ###   ########.fr       */
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

int		insert_char(t_d_list *entry, int c, size_t prompt_length, size_t *pos)
{
	char	*new_buff;

	if (!*(char *)entry->content)
	{
		ft_swapnfree(&(entry->content),ft_memalloc(tgetnum("co") - prompt_length + 1));
		entry->content_size = tgetnum("co") - prompt_length + 1;
	}
	else if (entry->content_size == ft_strlen(entry->content) - 1)
	{
		new_buff = ft_memalloc(entry->content_size + tgetnum("co"));
		ft_strcpy(new_buff, entry->content);
		free(entry->content);
		entry->content = new_buff;
		entry->content_size += tgetnum("co");
		//term scroll up
	}
	tputs(tgetstr("im", NULL), 1, ft_putint);
	ft_putint(c);
	tputs(tgetstr("ei", NULL), 1, ft_putint);
	entry->content_size += ft_strinsert(entry->content, c, *pos);
	(*pos)++;
	return (1);
}