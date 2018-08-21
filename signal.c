/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:21:00 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/21 16:34:26 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

void	signal_handle(int sig)
{
	char	**env;

	env = NULL;
	(void)env;
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		prompt(g_env);
	}
}

void	ignore_child_signal(int sig)
{
	if (sig == SIGINT)
		ft_putchar('\n');
}
