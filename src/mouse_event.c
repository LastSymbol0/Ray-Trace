/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:55:32 by aillia            #+#    #+#             */
/*   Updated: 2019/09/24 17:55:38 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_obj	*mouse_click(t_scene *sc)
{
	t_obj	*obj;
	int		mouse_x;
	int		mouse_y;

	SDL_GetMouseState(&mouse_x, &mouse_y);
	obj = cast_ray(sc, get_ray(sc, mouse_x, mouse_y));
	return (obj);
}

void	mouse_move(t_scene *sc, SDL_Event evt)
{
	sc->cam.rot.x += evt.motion.xrel / 10;
	sc->cam.rot.y += evt.motion.yrel / 10;
	if (sc->cam.rot.x > 360)
		sc->cam.rot.x = sc->cam.rot.x - 360;
	if (sc->cam.rot.y > 360)
		sc->cam.rot.y = sc->cam.rot.y - 360;
	if (sc->cam.rot.x < 0)
		sc->cam.rot.x = 360 - sc->cam.rot.x;
	if (sc->cam.rot.y < 0)
		sc->cam.rot.y = 360 - sc->cam.rot.y;
	set_ray_arr_ocl_3(sc);
	ray_trace_2(sc);
	sdl_draw(sc);
}
