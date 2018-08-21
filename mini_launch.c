/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 12:46:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/21 16:34:26 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

static char	*exec_location(char *path, char **env)
{
	char	**path_env;
	char	**dup;
	char	*exec;

	if (!access(path, F_OK))
		return (ft_strdup(path));
	path_env = ft_strsplit(ft_getenv("PATH", env), ':');
	dup = path_env;
	if (!dup)
		return (NULL);
	while (*dup)
	{
		exec = ft_strmjoin(3, *dup, "/", path);
		if (!access(exec, F_OK))
			break ;
		free(exec);
		exec = NULL;
		dup++;
	}
	ft_tabfree(path_env);
	free(path_env);
	return (exec);
}

int			mini_launch(char *argv[], char *env[])
{
	char	*exec;
	int		status;

	status = 0;
	exec = exec_location(argv[0], env);
	if (!exec)
		return (ft_puterr(SHELL_NAME, argv[0], "command not found", 1));
	else if (access(exec, X_OK))
	{
		free(exec);
		return (ft_puterr(SHELL_NAME, argv[0], "permission denied", 1));
	}
	signal(SIGINT, ignore_child_signal);
	if (fork())
	{
		wait4(-1, &status, 0, NULL);
		free(exec);
		signal(SIGINT, signal_handle);
		return (status);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		return (execve(exec, argv, env));
	}
}
