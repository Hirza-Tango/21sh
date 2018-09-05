/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:51:34 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/05 18:30:10 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twentyonesh.h>

int		default_path(char ***env)
{
	const int	fd = open("/etc/paths", O_RDONLY);
	char		*input;
	char		*path;
	char		*temp;

	path = NULL;
	while (get_next_line(fd, &input) > 0)
	{
		if (path)
		{
			temp = ft_strmjoin(3, path, ":", input);
			free(path);
			path = temp;
		}
		else
			path = input;
	}
	ft_setenv("PATH", path, env);
	close(fd);
	return (0);
}

char	*abs_to_rel(char *old, char **env, int reverse)
{
	const char	*find = reverse ? "~" : ft_getenv("HOME", env);
	const char	*replace = (!reverse) ? "~" : ft_getenv("HOME", env);

	if (!env || !ft_getenv("HOME", env))
		return (ft_strdup(old));
	if (!ft_strncmp(old, find, ft_strlen(find)))
		return (ft_strjoin(replace, old + ft_strlen(find)));
	return (ft_strdup(old));
}

void	substitutions(char **tab, char **env)
{
	while (*tab)
	{
		if (**tab == '~')
			ft_swapnfree((void **)tab, abs_to_rel(*tab, env, 1));
		if (**tab == '$' && (*tab)[1] != '?' && (*tab)[1] != '@')
			ft_swapnfree((void **)tab, ft_getenv(*tab + 1, env) ?
				ft_strdup(ft_getenv(*tab + 1, env)) : ft_strdup(""));
		tab++;
	}
}

int		ft_puterr(const char *command, const char *target,
	const char *reason, int code)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (*target)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(reason, 2);
	return (code);
}

char	*prompt(char **env)
{
	char	*wd;
	char	*ret;

	if (!env)
		return ("\e[31m$>\e[0m");
	wd = getcwd(NULL, 0);
	ft_swapnfree((void **)&wd, abs_to_rel(wd, env, 0));
	ret = ft_strmjoin(5, "\e[32m", ft_getenv("USER", env), "\e[31m@\e[36m", wd,
		"\e[31m#\e[0m ");
	free((char *)wd);
	return (ret);
}
