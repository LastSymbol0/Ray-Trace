/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:25:36 by aillia            #+#    #+#             */
/*   Updated: 2019/09/29 15:25:38 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

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
	ft_putendl("Redraw");
	ray_trace_3(sc);
	sdl_draw(sc);
}

void	redraw_scene(t_scene *sc)
{
	ft_putendl("Redraw");
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
