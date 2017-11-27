/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmiceli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 23:11:28 by pmiceli           #+#    #+#             */
/*   Updated: 2017/11/28 00:19:04 by pmiceli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>

int		main(int argc, const char *argv[])
{
	char	*line;
	int		fd;
	int		i;
	int		res;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while ((res = get_next_line(fd, &line)) != 0)
	{
		ft_putstr_color(line, "grey");
		i++;
		ft_putnbr_endl(res);
	}
	return (0);
}
