/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:16:43 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/21 16:38:41 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

static char	**init_env(char **env)
{
	char	**ret;
	char	*newlvl;

	ret = ft_tabdup(env);
	if (!ft_getenv("PATH", ret))
		default_path(&ret);
	ft_setenv("SHELL", ft_getenv("_", ret), &ret);
	newlvl = ft_itoa(ft_atoi(ft_getenv("SHLVL", ret)) + 1);
	ft_setenv("SHLVL", newlvl, &ret);
	free(newlvl);
	return (ret);
}

int			main(int argc, char *argv[], char *envv[])
{
	char		*input;
	int			status;

	(void)(argv && argc);
	g_env = init_env(envv);
	status = 0;
	signal(SIGINT, signal_handle);
	while (1)
	{
		prompt(g_env);
		input = editor();
		parser(input, &status);
		free(input);
	}
}
