/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmiceli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:46:55 by pmiceli           #+#    #+#             */
/*   Updated: 2017/11/30 16:05:52 by pmiceli          ###   ########.fr       */
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
	int i;

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
	int		i;
	int		j;
	char	*before;

	gnl->i = ft_get_pos(buff);
	j = 0;
//	if (buff[BUFF_SIZE - 1] == '\n')
//		return (ft_strjoin_free(line, buff));
	if (!(before = (char *)malloc(sizeof(char) * gnl->i + 1)))
		return (NULL);
	if (!(gnl->after = (char *)malloc(sizeof(char) *
					(BUFF_SIZE - gnl->i - 1))))
		return (NULL);
	i = 0;
	while (buff[i] != '\n' && i < BUFF_SIZE)
	{
		before[i] = buff[i];
		i++;
	}
	before[i] = '\0';
	i++;
	while (i < BUFF_SIZE)
		gnl->after[j++] = buff[i++];
	gnl->after_len = ft_strlen(gnl->after);
	return (ft_strjoin_free(line, before));
}

static char		*ft_before_after_tmp(char *tmp, t_gnl *gnl, char *line)
{
	int		i;
	int		j;
	int		k;
	char	*tmp_before;

	k = ft_get_pos(tmp);
	if (!(tmp_before = (char *)malloc(sizeof(char) * k + 1)))
		return (NULL);
	if (!(gnl->tmp_after = (char *)malloc(sizeof(char) * ft_strlen(tmp) - k - 1)))
		return (NULL);
	i = 0;
	while (tmp[i] != '\n' && i < ft_strlen (tmp))
	{
		tmp_before[i] = tmp[i];
		i++;
	}
	tmp_before[i] = '\0';
	i++;
	while (i < ft_strlen(tmp))
		gnl->tmp_after[j++] = tmp[i++];
	return (ft_strjoin(line, tmp_before));
}

int				get_next_line(const int fd, char **line)
{
	int				ret;
	int				i;
	int				j;
	char			buff[BUFF_SIZE];
	char			*tmp;
	static t_gnl	gnl;

	i = 0;
	j = 0;
	if (fd < 0 || BUFF_SIZE == 0 || fd > OPEN_MAX)
		return (-1);
	if ((gnl.after_len) && gnl.after_len > 0 && !gnl.tmp_after)
		*line = ft_strjoin("\0", gnl.after);
	else
		*line = ft_strnew(1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ft_strchr(buff, '\n') != NULL)
		{
			*line = ft_before_after(buff, &gnl, *line);
			return (1);
		}
		else
			*line = ft_strjoin_free(*line, buff);
	}
	ft_putendl_color(*line, "yellow");
	if (!(ret))
	{
		if (ft_strlen(*line) == 0)
			return (0);
		if (!(tmp = (char *)ft_memalloc(sizeof(char) * ft_strlen(*line))))
			return (-1);
		if (!(gnl.tmp_after))
			tmp = ft_memcpy(tmp, *line, ft_strlen(*line));
		else
			tmp = ft_memcpy(tmp, gnl.tmp_after, ft_strlen(gnl.tmp_after));
		free(*line);
		*line =  ft_before_after_tmp(tmp, &gnl, *line);
		return (1);
	}
	return (1);
}
