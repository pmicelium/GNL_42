/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmiceli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:46:55 by pmiceli           #+#    #+#             */
/*   Updated: 2017/11/28 17:45:58 by pmiceli          ###   ########.fr       */
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
	while (i < BUFF_SIZE)
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
	if (buff[BUFF_SIZE - 1] == '\n')
		return (ft_strjoin_free(line, buff));
	if (!(before = (char *)malloc(sizeof(char) * gnl->i + 1)))
		return (NULL);
	if (!(gnl->after = (char *)malloc(sizeof(char) *
					(BUFF_SIZE - gnl->i - 1))))
		return (NULL);
	i = 0;
//			TEST;
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
//	ft_putstr_color(gnl->after, "yellow");
//	ft_putnbr_endl(gnl->after_len);
	return (ft_strjoin_free(line, before));
}

int				get_next_line(const int fd, char **line)
{
	int				ret;
	char			buff[BUFF_SIZE];
	static t_gnl	gnl;

	if ((gnl.after_len) && gnl.after_len != 0)
	{
//		TEST;
		*line = ft_strjoin("\0", gnl.after);
	}
	else
		*line = ft_strnew(1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
//			ft_putendl_color(buff, "pink");
		if (ft_strchr(buff, EOF) != NULL)
		{
//			TEST;
			*line = ft_strjoin_free(*line, buff);
//			ft_putendl_color(*line, "red");
			return (0);
		}
		else if (ft_strchr(buff, '\n') != NULL)
		{
			*line = ft_before_after(buff, &gnl, *line);
//			ft_putendl_color(*line, "green");
			return (1);
		}
		else
			*line = ft_strjoin_free(*line, buff);
//			ft_putendl_color(*line, "yellow");
	}
	if (!ret)
	{
	//	ft_memdel((void**)line;
	//	ft_putendl_color(*line, "green");
		if ((*line) && ft_strchr(*line, '\n') != NULL)
		{
	//		free(gnl.after);
			*line = ft_strchr(*line, '\n');
			gnl.after_len = 0;
			return (1);
		}
		return (0);
	}
	return (1);
}
