/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 10:59:21 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/04 16:57:54 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		ctrl_arrow_up(void)
{
	return (-1);
}

int		ctrl_arrow_down(void)
{
	return (-1);
}

int		ctrl_arrow_left(size_t prompt_len, size_t *pos, char *content)
{
	while (*pos && ft_isspace(content[*pos - 1]) && arrow_left(prompt_len, pos))
		PASS;
	while (*pos && !ft_isspace(content[*pos - 1]) && arrow_left(prompt_len, pos))
		PASS;
	return (1);
}

int		ctrl_arrow_right(size_t prompt_len, size_t *pos, char *content)
{
	while (*pos <= ft_strlen(content) && ft_isspace(content[*pos]) && arrow_right(prompt_len, pos, content))
		PASS;
	while (*pos <= ft_strlen(content) && !ft_isspace(content[*pos]) && arrow_right(prompt_len, pos, content))
		PASS;
	return (1);
}
