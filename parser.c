/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 16:24:05 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/29 14:39:11 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twentyonesh.h>

static void	set_underscore(char **argv, char ***env)
{
	while (*argv)
		argv++;
	argv--;
	ft_setenv("_", *argv, env);
}

static void	call_handler(char *argv[], char ***env, int *status)
{
	if (ft_strequ(argv[0], "echo"))
		*status = mini_echo(argv);
	else if (ft_strequ(argv[0], "cd"))
		*status = mini_cd(argv, env);
	else if (ft_strequ(argv[0], "pwd"))
		*status = mini_pwd();
	else if (ft_strequ(argv[0], "setenv"))
		*status = mini_setenv(argv, env);
	else if (ft_strequ(argv[0], "unsetenv"))
		*status = mini_unsetenv(argv, env);
	else if (ft_strequ(argv[0], "env"))
		*status = mini_env(argv, env);
	else if (ft_strequ(argv[0], "exit") || ft_strequ(argv[0], "q"))
	{
		ft_tabfree(*env);
		exit(argv[1] ? ft_atoi(argv[1]) : *status);
	}
	else if (ft_strequ(argv[0], "$?"))
	{
		ft_putnbr(*status);
		ft_putchar('\n');
	}
	else
		*status = mini_launch(argv, *env);
	set_underscore(argv, env);
}

int	parser(const char *input, int *status)
{
	char		**bigargs;
	char		**dup;
	char		**args;

	if (!(bigargs = ft_strsplit(input, ';')))
		return (1);
	dup = bigargs;
	while (*dup)
	{
		if (!(args = ft_strqotsplit(*dup)))
		{
			dup++;
			continue;
		}
		substitutions(args, g_env);
		call_handler(args, &g_env, status);
		ft_tabfree(args);
		free(args);
		dup++;
	}
	ft_tabfree(bigargs);
	free(bigargs);
	return (0);
}