/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:00:30 by aillia            #+#    #+#             */
/*   Updated: 2019/09/24 18:00:32 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	w_key_event(t_scene *sc)
{
	t_ray dir;

	dir = get_ray(sc, WIDTH / 2, HEIGHT / 2);
	sc->cam.pos = v_add(sc->cam.pos, dir.dir);
	set_ray_arr_ocl_2(sc);
	ray_trace_2(sc);
	sdl_draw(sc);
}

void	s_key_event(t_scene *sc)
{
	t_ray dir;

	dir = get_ray(sc, WIDTH / 2, HEIGHT / 2);
	sc->cam.pos = v_add(sc->cam.pos, v_scale(dir.dir, -1));
	set_ray_arr_ocl_2(sc);
	ray_trace_2(sc);
	sdl_draw(sc);
}
