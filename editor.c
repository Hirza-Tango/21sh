/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 16:16:25 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/21 16:36:43 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

char	*editor(void)
{
	char		*input;

	if (get_next_line(0, &input) <= 0)
	{
		ft_putendl("exit");
		exit(1);
	}
	return (input);
}