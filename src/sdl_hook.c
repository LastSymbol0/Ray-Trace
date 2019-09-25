/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:46:54 by aillia            #+#    #+#             */
/*   Updated: 2019/09/11 17:46:56 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"


void	hook(t_scene *sc)
{
	int running = 1;
	SDL_Window *win;
	SDL_GLContext glContext;
	struct nk_color background;
	struct nk_context *ctx;
	struct nk_colorf bg;

	sc->mouse_move_enable = 0;
	win = SDL_CreateWindow("Info", 200, 200, I_OBJ_WIDTH, I_OBJ_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
	glContext = SDL_GL_CreateContext(win);
	ctx = nk_sdl_init(win);
	strange_fonts_magic(ctx);
	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
	while (running)
	{
		main_evt(ctx, win, glContext, sc);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(bg.r, bg.g, bg.b, bg.a);

		nk_sdl_render(NK_ANTI_ALIASING_ON);
		SDL_GL_SwapWindow(win);
	}
}