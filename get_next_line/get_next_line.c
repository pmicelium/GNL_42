/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmiceli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:46:55 by pmiceli           #+#    #+#             */
/*   Updated: 2017/11/29 00:09:30 by pmiceli          ###   ########.fr       */
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
	ft_putendl_color(gnl->after, "green");
	return (ft_strjoin_free(line, before));
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
	if ((gnl.after_len) && gnl.after_len > 0)
	{
		*line = ft_strjoin("\0", gnl.after);
		ft_putendl_color(*line, "grey");
	}
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
	if (!ret) //essayer de faire la meme boucle que le read sauf que le buff est remplacer par le gnl.after//
	{
		if (gnl.after_len > 0)
		{
			ft_putnbr_endl(gnl.after_len);
			tmp = ft_strnew(gnl.after_len);
			tmp = ft_memcpy(tmp, gnl.after, gnl.after_len);
			while (i < gnl.after_len)
			{
				if (i == 0 && tmp[i] == '\n')
					tmp++;
				if (tmp[i] == '\n')
				{
						tmp[i] = '\0';
						break ;
				}
				i++;
			}
			TEST;
			ft_putendl_color(gnl.after, "green");
			ft_putendl_color(tmp, "cyan");
			*line = tmp;
			ft_putendl_color(*line, "red");
		//	free(tmp);
			gnl.after = ft_strchr(gnl.after, '\n');
			gnl.after_len = ft_strlen(gnl.after);
			ft_putnbr_endl(gnl.after_len);
		}
	}
	return (1);
}
