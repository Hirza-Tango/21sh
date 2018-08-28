/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 16:16:25 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/28 13:29:17 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>


char	*editor(t_d_list **history)
{
	char		*input;
	t_d_list	*dup;

	input = NULL;
	ft_dlstadd(history, ft_dlstnew(&input, sizeof(char **)));
	if (get_next_line(0, &input) <= 0)
	{
		ft_putendl("exit");
		exit(1);
	}
	return (input);
}
