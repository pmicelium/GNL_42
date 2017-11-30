/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bacrozat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:13:54 by bacrozat          #+#    #+#             */
/*   Updated: 2017/11/17 21:00:48 by bacrozat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/syslimits.h>
#include "get_next_line.h"

static char		*ft_doit(char **line, char *left)
{
	char *tmp;

	if (ft_strchr(left, '\n'))
	{
		*ft_strchr(left, '\n') = '\0';
		*line = left;
		tmp = ft_strdup(&left[ft_strlen(left) + 1]);
		return (tmp);
	}
	if (ft_strlen(left))
	{
		*line = left;
		left = ft_strdup(&left[ft_strlen(left)]);
		return (left);
	}
	return (NULL);
}

int				get_next_line(int const fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char *left[OPEN_MAX];
	int			ret;
	char		*tmp;

	if (fd < 0 || fd >= OPEN_MAX)
		return (-1);
	if (!(left[fd]))
		if (!(left[fd] = ft_strnew(BUFF_SIZE)))
			return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (ret);
		buf[ret] = '\0';
		tmp = ft_strjoin(left[fd], buf);
		free(left[fd]);
		left[fd] = tmp;
		if (ft_strchr(left[fd], '\n'))
			break ;
	}
	return ((left[fd] = ft_doit(line, left[fd])) ? 1 : 0);
}
