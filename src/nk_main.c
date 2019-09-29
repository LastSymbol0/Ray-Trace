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

void	main_evt_h(t_scene *sc, SDL_Event evt)
{
	if (sc->mouse_move_enable == 1 && evt.type == SDL_MOUSEMOTION)
		mouse_move(sc, evt);
	else if (evt.type == SDL_KEYDOWN &&
								SDL_SCANCODE_SPACE == evt.key.keysym.scancode)
		CLICK_CLACK(sc->mouse_move_enable);
	else if (evt.type == SDL_KEYDOWN &&
									SDL_SCANCODE_P == evt.key.keysym.scancode)
		save_screenshot_bmp(sc);
	else if (evt.type == SDL_KEYDOWN &&
									SDL_SCANCODE_W == evt.key.keysym.scancode)
		w_key_event(sc);
	else if (evt.type == SDL_KEYDOWN &&
									SDL_SCANCODE_S == evt.key.keysym.scancode)
		s_key_event(sc);
}

void	main_evt_hh(struct nk_context *ctx, SDL_Window *win,
									SDL_GLContext gl_context, SDL_Event evt)
{
	if (evt.type == SDL_QUIT ||
							SDL_SCANCODE_ESCAPE == evt.key.keysym.scancode)
		nk_exit(ctx, win, gl_context);
}

void	main_evt(struct nk_context *ctx, SDL_Window *win,
										SDL_GLContext gl_context, t_scene *sc)
{
	static t_obj	*obj;
	t_obj			tmp;
	SDL_Event		evt;

	nk_input_begin(ctx);
	while (SDL_PollEvent(&evt))
	{
		main_evt_hh(ctx, win, gl_context, evt);
		if (evt.window.windowID == SDL_GetWindowID(sc->sdl->window))
		{
			if (evt.type == SDL_MOUSEBUTTONDOWN)
				obj = mouse_click(sc);
			main_evt_h(sc, evt);
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
