/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmiceli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:42:53 by pmiceli           #+#    #+#             */
/*   Updated: 2017/11/28 00:03:25 by pmiceli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32
# include "libft/libft.h"

typedef struct	s_param
{
	int			i;
	char		*after;
}				t_param;

int				get_next_line(const int fd, char **line);

#endif
