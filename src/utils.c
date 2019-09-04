/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:52:21 by aillia            #+#    #+#             */
/*   Updated: 2019/08/13 16:52:23 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_fcolor	get_fcolor(t_color color)
{
	t_fcolor	fcolor;

	fcolor.red = color.red / 255.;
	fcolor.green = color.green / 255.;
	fcolor.blue = color.blue / 255.;
	return (fcolor);
}

void	pixel_put(int color)
{
	if (color < 0)
		color = 0;
}

void	ft_err(char *err, int status)
{
	if (status == 1)
		ft_putstr("Error: ");
	ft_putendl(err);
	exit(status);
}

void	set_tabs(int n)
{
	int i;

	i = -1;
	while (++i < n)
		printf("\t");
}

int		arr_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	*read_file(char *filename, size_t file_size)
{
	int		fd;
	char	*res;

	fd = open(filename, O_RDONLY);
	printf("filename:%s; fd:%d\n", filename, fd);
	res = ft_strnew(file_size);
	read(fd, res, file_size);
	close(fd);
	return (res);
}