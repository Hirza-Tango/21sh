/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:45:55 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/26 16:33:40 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_PARSER_H
# define FT_SHELL_PARSER_H

# include <libft.h>
# include "../ft_readline/ft_readline.h"

enum	e_tokens
{
	T_WORD,
	T_PIPE,
	T_EOF,
	T_OPERATOR,
};

typedef struct	s_token
{
	int				type;
	char			*token;
	struct s_token	*next;
}				t_token;

char	*token_list(const char *prompt);
char	*ft_get_full_line(const char *prompt);
char	*continue_dquote(char **s, size_t *pos);
char	*continue_squote(char **s, size_t *pos);
char	*continue_lit(char **s, size_t *pos);

#endif
