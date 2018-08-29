/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 17:21:15 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/29 14:39:11 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twentyonesh.h>

int		mini_setenv(char *argv[], char ***env)
{
	if (!argv[1])
		return (mini_env(argv, env));
	return (ft_setenv(argv[1], argv[2] ? argv[2] : "", env));
}
