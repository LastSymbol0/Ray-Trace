/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:05:08 by aillia            #+#    #+#             */
/*   Updated: 2019/09/25 18:05:10 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	main_evt(struct nk_context *ctx, SDL_Window *win, SDL_GLContext glContext, t_scene *sc)
{
	static t_obj	*obj;
	t_obj			tmp;
	// t_obj			*empty;
	SDL_Event		evt;

	// obj = NULL;
	// empty = (t_obj *)ft_memalloc(sizeof(obj));
	// empty->type = CAM;
	// empty->rot = v_norm(empty->rot);
	nk_input_begin(ctx);
	while (SDL_PollEvent(&evt))
	{
		if (evt.type == SDL_QUIT || SDL_SCANCODE_ESCAPE == evt.key.keysym.scancode)
			nk_exit(ctx, win, glContext);
		if (evt.window.windowID == SDL_GetWindowID(sc->sdl->window) && evt.key.repeat == 0)
		{
			if (evt.type == SDL_MOUSEBUTTONDOWN)
				obj = mouse_click(sc);
			else if (sc->mouse_move_enable == 1 && evt.type ==  SDL_MOUSEMOTION)
				mouse_move(sc, evt);
			else if (evt.type == SDL_KEYDOWN && SDL_SCANCODE_SPACE == evt.key.keysym.scancode)
				sc->mouse_move_enable == 0 ? sc->mouse_move_enable = 1 : (sc->mouse_move_enable = 0);
			else if(evt.type == SDL_KEYDOWN && SDL_SCANCODE_P == evt.key.keysym.scancode)
				saveScreenshotBMP(sc);
			else if (evt.type == SDL_KEYDOWN && SDL_SCANCODE_W == evt.key.keysym.scancode)
				w_key_event(sc);
			else if (evt.type == SDL_KEYDOWN && SDL_SCANCODE_S == evt.key.keysym.scancode)
				s_key_event(sc);
		}
		else
			nk_sdl_handle_event(&evt);
	}
	nk_input_end(ctx);
	if (obj == NULL)
		obj = &sc->objects[2];
	tmp = *obj;
	scene_win(ctx, sc);
	obj_win(ctx, obj, sc);
	if (!obj_equal(tmp, *obj))
		redraw_obj(sc);
}
