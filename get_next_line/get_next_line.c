/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmiceli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:46:55 by pmiceli           #+#    #+#             */
/*   Updated: 2017/11/27 21:01:02 by pmiceli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <limits.h>
#include <fcntl.h>
#define TEST ft_putendl_color("TEST", "cyan");

typedef struct	s_param
{
	int			i;
	char		*after;
}				t_param;

static int		ft_buff_check(char *buff, t_param param)
{
	param.i = 0;
	while (buff[param.i])
	{
		if (buff[param.i] == '\n')
			return (1);//retourne 1 si j'ai un \n dans mon buff//
		if (buff[param.i] == '\0')
			return (2); //retourne 2 si j'ai un \0 dans mon buff//
		param.i++;
	}
	return (0);// aucun char special dans le buffer//
}

static char		*ft_before_after(char *buff, t_param param, char *line)
{
	int		i;
	int		j;
	char	*before;

	j = 0;
	if (!(before = (char *)malloc(sizeof(char) * param.i)))
		return (NULL);
	if (!(param.after = (char *)malloc(sizeof(char) * (ft_strlen(buff) - param.i))))
		return (NULL);
	i = 0;
	while (buff[i] != '\n')
	{
		before[i] = buff[i];
		i++;
	}
	while (buff[i])
	{
		param.after[j] = buff[i];
		j++;
		i++;
	}
	return (ft_strjoin(line, before));
}

int				get_next_line(const int fd, char **line)
{
	int					ret;
	char				buff[BUFF_SIZE];
	static t_param		param;


	*line = ft_strjoin("\0", "\0");
	if (!(fd))
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE - 1)))
	{
		buff[ret] = '\0';
		if (ft_buff_check(buff, param) == 1) //si j'ai un \n dans mon buff//
		{
			*line = ft_before_after(buff, param, *line);
			return (1);
		}
		else if (ft_buff_check(buff, param) == 2)
		{
			ft_strjoin(*line, buff);
			return (0);
		}
		else
			*line = ft_strjoin(*line, buff);
	}
	return (-1);
}
