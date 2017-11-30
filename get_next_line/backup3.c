/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmiceli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:46:55 by pmiceli           #+#    #+#             */
/*   Updated: 2017/11/30 19:57:15 by pmiceli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#define TEST ft_putendl_color("TEST", "cyan");

static int		ft_get_pos(char *buff)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(buff))
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

static char		*ft_before_after(char *buff, t_gnl *gnl, char *line)
{
	size_t		i;
	int		j;
	int		k;
	char	*before;

	k = ft_get_pos(buff);
	j = 0;
	if (!(before = (char *)malloc(sizeof(char) * k + 1)))
		return (NULL);
	if (!(gnl->after = (char *)malloc(sizeof(char) *
					(ft_strlen(buff) - k - 1))))
		return (NULL);
	i = 0;
	while (buff[i] != '\n' && i < ft_strlen(buff))
	{
		before[i] = buff[i];
		i++;
	}
	before[i] = '\0';
	i++;
	if (i != ft_strlen(buff))
	{
	while (i < ft_strlen(buff))
		gnl->after[j++] = buff[i++];
	gnl->after_len = ft_strlen(gnl->after);
	}
	else
		free(gnl->after);
	return (ft_strjoin(line, before));
}

int				get_next_line(const int fd, char **line)
{
//	int				ret;
	int				i;
	int				j;
	char			buff[BUFF_SIZE];
	char			*tmp;
	static t_gnl	gnl;

	i = 0;
	j = 0;
	if (fd < 0 || BUFF_SIZE == 0 || fd > OPEN_MAX)
		return (-1);
	if ((gnl.after_len) && gnl.after_len > 0)
		*line = ft_strjoin("\0", gnl.after);
	else
		*line = ft_strnew(1);
	while ((gnl.ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ft_strchr(buff, '\n') != NULL)
		{
			*line = ft_before_after(buff, &gnl, *line);
			return (1);
		}
		else
			*line = ft_strjoin_free(*line, buff);
	}
	if (!(gnl.ret))
	{
		if ((gnl.after) && gnl.after_len > 0)
		{
			if (!(tmp = (char*)malloc(sizeof(char) * gnl.after_len)))
				return (-1);
			tmp = ft_memcpy(tmp, gnl.after, gnl.after_len);
			free(*line);
		}
		else if (*line && gnl.i != 1)
		{
			gnl.i = 1;
			return (1);
		}
		else if (gnl.i == 1)
			return (0);
		if (ft_strchr(tmp, '\n') != NULL)
		{
			*line = ft_before_after(tmp, &gnl, *line);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}
