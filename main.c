/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:16:43 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/10 17:19:01 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_puterr(const char *command, const char *target, const char *reason)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (*target)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(reason, 2);
	exit(1);
}

void	ft_tabfree(char **tab)
{
	char	**dup;

	if (!tab)
		return ;
	dup = tab;
	while (*dup)
		free(*dup++);
	free(dup);
	free(tab);
	tab = NULL;
}

void	terminate(int sig)
{
	if (sig == 15)
		exit(0);
}

void	call_handler(char *argv[])
{
	if (ft_strequ(argv[0], "echo"))
		mini_echo(argv);
	else if (ft_strequ(argv[0], "cd"))//fix?
		mini_cd(argv);
	else if (ft_strequ(argv[0], "pwd"))
		mini_pwd();
	/*else if (ft_strequ(argv[0], "setenv"))
		mini_setenv(argv, env);
	else if (ft_strequ(argv[0], "unsetenv"))
		mini_unsetenv(argv, env);
	else if (ft_strequ(argv[0], "env"))
		mini_env(argv, env);*/
	else if (ft_strequ(argv[0], "exit") || ft_strequ(argv[0], "q"))
		kill(0, 15) ? ft_putendl("Patricide/Matricide attempt failed.") : 0;
	/*else
		mini_launch(argv, env);*/
	exit(0);
}

int		main(int argc, char *argv[])
{
	char	*input;
	int		status;
	pid_t	pid;
	char	**args;

	(void)(argv && argc);
	while (1)
	{
		ft_putstr("$> ");
		if (get_next_line(0, &input) <= 0)
		{
			ft_putendl("Failed to read output. Terminating...");
			exit(1);
		}
		if (!(args = ft_strsplit(input, ' ')))
			continue;
		//TODO: split on all whitespace
		if (!(pid = fork()))
			call_handler(args);
		else if (pid < 0)
			ft_putendl("Fork() failed. Please ensure enough resorces are free");
		//ft_tabfree(args);//TODO: fix
		signal(15, terminate);
		wait(&status);
		//TODO: handle status codes
	}
}
