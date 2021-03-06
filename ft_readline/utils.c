/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:12:52 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/09 21:45:58 by dslogrov         ###   ########.fr       */
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

size_t		prompt_len(const char *prompt)
{
	char	*temp;
	size_t	ret;

	temp = (char *)prompt;
	ret = 0;
	while (*temp)
	{
		if (*temp == '\e')
			while (*temp != 'm' && temp[1])
				temp++;
		else
			ret++;
		temp++;
	}
	return (ret);
}

int			ft_putint(int c)
{
	char	ch;

	ch = c;
	write(1, &ch, 1);
	return (c);
}
