/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:16:43 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/27 13:49:47 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twentyonesh.h>

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
	char		*p;
	int			status;

	(void)(argv && argc);
	if (!isatty(0))
		exit(2);
	g_env = init_env(envv);
	status = 0;
	//signal(SIGINT, signal_handle);
	tgetent(NULL, ft_getenv("TERM", g_env));
	while (1)
	{
		p = prompt(g_env);
		input = token_list(p, g_env);
		//parser(input, &status);
		free(input);
		//free(p);
	}
}
