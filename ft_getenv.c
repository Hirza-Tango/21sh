/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 10:44:10 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/29 14:39:11 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twentyonesh.h>

const char	*ft_getenv(const char *name, char **env)
{
	char			**dup;

	if (!name || !*name || ft_strchr(name, '=') || !env)
		return (NULL);
	dup = env;
	while (*dup)
	{
		if (!ft_strncmp(*dup, name, ft_strlen(name)) &&
			(*dup)[ft_strlen(name)] == '=')
			return (*dup + ft_strlen(name) + 1);
		dup++;
	}
	return (NULL);
}
