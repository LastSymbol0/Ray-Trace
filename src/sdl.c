/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:39:46 by aillia            #+#    #+#             */
/*   Updated: 2019/08/14 17:39:48 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	test_sdl(t_scene *sc)
{
	int	x;
	int	y;
	int running;

	running = 1;
	y = -1;
	while(++y < HEIGHT)
	{
		x = -1;
		while(++x < WIDTH)
			sdl_put_pixel(sc, x, y, 1233454);
	}
	sdl_draw(sc);
	
	while (running)
		while(!SDL_PollEvent (&sc->sdl->event))
			if (SDL_QUIT == sc->sdl->event.type || SDL_SCANCODE_ESCAPE == sc->sdl->event.key.keysym.scancode)
				running = 0;
	sdl_destroy(sc);
}

t_SDL	*sdl_init(t_scene *sc)
{
	t_SDL	*sdl;

	sdl = (t_SDL *)ft_memalloc(sizeof(t_SDL));
	sdl->pixel = (Uint32 *)ft_memalloc(sizeof(Uint32) * HEIGHT * WIDTH);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_err("SDL init error", 1);
	sdl->window = SDL_CreateWindow(sc->name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);
	sdl->render = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
	sdl->texture = SDL_CreateTexture(sdl->render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
	return (sdl);
}

void	sdl_draw(t_scene *sc)
{
	SDL_UpdateTexture(sc->sdl->texture, NULL, sc->sdl->pixel, WIDTH * sizeof(Uint32));
	SDL_RenderClear(sc->sdl->render);
	SDL_RenderCopy(sc->sdl->render, sc->sdl->texture, NULL, NULL);
	SDL_RenderPresent(sc->sdl->render);
}

void	sdl_destroy(t_scene *sc)
{
	SDL_DestroyTexture(sc->sdl->texture);
	SDL_DestroyRenderer(sc->sdl->render);
	SDL_DestroyWindow(sc->sdl->window);
}

void	sdl_put_pixel(t_scene *sc, int x, int y, int color)
{
	sc->sdl->pixel[y * WIDTH + x] = color < 0 ? 0 : color;
}