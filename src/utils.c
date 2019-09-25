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


char	*get_string_obj_type(int type)
{
	if (type == SPHERE)
		return ("sphere");
	if (type == PLANE)
		return ("plane");
	if (type == CYLINDER)
		return ("cylinder");
	if (type == CONE)
		return ("cone");
	return ("null");
}

float	fequalizer(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

int		equalizer(int value, int min, int max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

void	redraw_obj(t_scene *sc)
{
	ft_putendl("Redraw obj");
	ray_trace_3(sc);
	sdl_draw(sc);
}

void	redraw_scene(t_scene *sc)
{
	ft_putendl("Redraw scene");
	set_ray_arr_ocl_3(sc);
	ray_trace_4(sc);
	sdl_draw(sc);
}

int		fcolor_equal(t_fcolor a, t_fcolor b)
{
	if (a.red != b.red || a.blue != b.blue || a.green != b.green)
		return (0);
	return (1);
}

int		float3_equal(cl_float3 a, cl_float3 b)
{
	if (fabs(a.x - b.x) > 0.0001 || fabs(a.y - b.y) > 0.0001 || fabs(a.z - b.z) > 0.0001)
		return (0);
	return (1);
}

int		obj_equal(t_obj a, t_obj b)
{
	if (a.radius != b.radius)
		return (0);
	if (a.type != b.type)
		return (0);
	if (!fcolor_equal(a.fcolor, b.fcolor))
		return (0);
	if (!float3_equal(a.pos, b.pos))
		return (0);
	if (!float3_equal(a.rot, b.rot))
		return (0);
	if (a.difuse != b.difuse )
		return (0);
	if (a.reflection_coef != b.reflection_coef )
		return (0);
	if (a.transparency_coef != b.transparency_coef )
		return (0);
	if (a.refract_coef != b.refract_coef )
		return (0);
	return (1);
}