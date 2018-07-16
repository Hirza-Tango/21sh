/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:56:50 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/16 14:01:45 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_tabfree(char **tab)
{
	char	**dup;

	if (!tab)
		return ;
	dup = tab;
	while (*dup)
		free(*dup++);
	tab = NULL;
}
