/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:56:04 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/12 14:14:23 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_PARSER_H
# define TOKEN_PARSER_H

# include "../twentyonesh.h"

enum	e_tokens
{
	T_END = 0,
	T_DQUOTE,
	T_SQUOTE,
	T_SPACE,
	T_COMMENT,
	T_TOKEN,
	T_NEWLINE,
	T_WORD,
	T_NAME,
	T_ASSIGNMENT_WORD,
	T_IO_NUMBER,
	T_AND_IF,
	T_OR_IF,
	T_GREAT,
	T_LESS,
	T_PIPE,
	T_AMP,
	T_SEMI,
	T_DSEMI,
	T_DLESS,
	T_DGREAT,
	T_LESSAND,
	T_GREATAND,
	T_LESSGREAT,
	T_DLESSDASH,
	T_CLOBBER,
	T_IF,
	T_THEN,
	T_ELSE,
	T_ELIF,
	T_FI,
	T_DO,
	T_DONE,
	T_CASE,
	T_ESAC,
	T_WHILE,
	T_UNTIL,
	T_FOR,
	T_LBRACE
};

char	*token_list(const char *prompt);

#endif
