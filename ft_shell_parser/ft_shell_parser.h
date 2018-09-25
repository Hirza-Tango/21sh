/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:45:55 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/25 16:04:33 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_PARSER_H
# define FT_SHELL_PARSER_H

# include <libft.h>
# include "../ft_readline/ft_readline.h"

char	*token_list(const char *prompt);

#endif
