/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:45:55 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/27 15:54:46 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_PARSER_H
# define FT_SHELL_PARSER_H

# include <libft.h>
# include "../ft_readline/ft_readline.h"

enum			e_tokens
{
	T_WORD,
	T_PIPE,
	T_OPERATOR,
	T_SEMI,
	T_LESS,
	T_GREAT,
	T_OR_IF,
	T_AND_IF,
	T_DLESS,
	T_DGREAT,
	T_LESSAND,
	T_GREATAND,
	T_LESSGREAT
};

typedef struct	s_token
{
	int				type;
	char			*token;
	struct s_token	*next;
}				t_token;

char			*token_list(const char *prompt, char **env);

char			*continue_dquote(char **s, size_t *pos);
char			*continue_squote(char **s, size_t *pos);
char			*continue_lit(char **s, size_t *pos);
char			*continue_substitution(char **s, size_t *pos, char **env);

char			*ft_getenv(const char *name, char **env);

#endif
