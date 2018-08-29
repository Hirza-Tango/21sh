/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:27:14 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/29 15:31:34 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HISTORY_H
# define FT_HISTORY_H

# include <libft.h>

typedef void	*t_histdata;

typedef struct	s_hist_entry
{
	char		*line;
	char		*timestamp;
	t_histdata	data;
}				t_hist_entry;

typedef struct	s_hist_state
{
	t_hist_entry	**entries;	/* Pointer to the entries themselves. */
	int				offset;		/* The location pointer within this array. */
	int				length;		/* Number of elements within this array. */
	int				size;		/* Number of slots allocated to this array. */
	int				flags;
}				t_hist_state;

#endif
