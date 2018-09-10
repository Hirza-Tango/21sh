/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:56:04 by dslogrov          #+#    #+#             */
/*   Updated: 2018/09/10 16:36:29 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_PARSER_H
# define TOKEN_PARSER_H

# include "../twentyonesh.h"

enum	tokens
{
	TOK_END = 0,
	TOK_TOKEN,
	TOK_NEWLINE,
	TOK_WORD,
	TOK_NAME,
	TOK_ASSIGNMENT_WORD,
	TOK_IO_NUMBER,
	TOK_AND_IF,
	TOK_OR_IF,
	TOK_DSEMI,
	TOK_DLESS,
	TOK_DGREAT,
	TOK_LESSAND,
	TOK_GREATAND,
	TOK_LESSGREAT,
	TOK_DLESSDASH,
	TOK_CLOBBER,
	TOK_IF,
	TOK_THEN,
	TOK_ELSE,
	TOK_ELIF,
	TOK_FI,
	TOK_DO,
	TOK_DONE,
	TOK_CASE,
	TOK_ESAC,
	TOK_WHILE,
	TOK_UNTIL,
	TOK_FOR,
	TOK_LBRACE
};

char	*token_list(const char *prompt);

#endif
