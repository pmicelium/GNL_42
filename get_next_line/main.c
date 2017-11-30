/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmiceli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 23:11:28 by pmiceli           #+#    #+#             */
/*   Updated: 2017/11/30 19:44:27 by pmiceli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

int		main(int argc, const char *argv[])
{
	char	*line;
	int		fd;
	int		i;
	int		res;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while (res > 0 && i < 30)
	{
		res = get_next_line(fd, &line);
		if (res != 0)
		{
			ft_putstr(line);
			ft_putstr_color("|", "red");
		}
		i++;
		ft_putnbr_endl(res);
	}

	return (0);
}
