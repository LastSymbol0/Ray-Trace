/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_sdl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:58:14 by aillia            #+#    #+#             */
/*   Updated: 2019/09/11 17:58:15 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_background(t_scene *sc)
{
	SDL_Surface *background = SDL_LoadBMP( "Fract.bmp" );
	SDL_BlitSurface(background, &((SDL_Rect){0, 0, I_WIDTH, I_HEIGHT}),
					sc->sdl->i_surface, &((SDL_Rect){0, 0, I_WIDTH, I_HEIGHT}));
	
	TTF_Font* brush_script = TTF_OpenFont("/Library/Fonts/Brush Script.ttf", 36);
	SDL_Color color = {255, 116, 0, 0};
	sc->sdl->i_offset_x = 210;
	sc->sdl->i_offset_y = 10;
	set_string(sc, "Info window", brush_script, color);
}

void	set_string(t_scene *sc, char *s, TTF_Font *font, SDL_Color color)
{
	SDL_Surface* surface_str;
	
	surface_str = TTF_RenderText_Blended_Wrapped(font, s, color, I_WIDTH); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_BlitSurface(surface_str, &((SDL_Rect){0, 0, surface_str->w, surface_str->h}),
					sc->sdl->i_surface, &((SDL_Rect){sc->sdl->i_offset_x, sc->sdl->i_offset_y, I_WIDTH, I_HEIGHT}));
}

void	make_text(t_scene *sc)
{
	TTF_Font* arial = TTF_OpenFont("/Library/Fonts/Brush Script.ttf", 28); //this opens a font style and sets a size
	if (!arial)
		ft_err("Open font err", 1);
	SDL_Color color = {255, 116, 0, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(arial, "Info window", color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_BlitSurface(surfaceMessage, &((SDL_Rect){0, 0, surfaceMessage->w, surfaceMessage->h}),
					sc->sdl->i_surface, &((SDL_Rect){10, 10, I_WIDTH, I_HEIGHT}));

	char s[200];
	sprintf(s, "Object:\n\tType: %d;\n\tPos: x: %f, y: %f, z: %f;\n\tColor: r: %d, g: %d, b: %d;\n",
			sc->objects[1].type,
			sc->objects[1].pos.x, sc->objects[1].pos.y, sc->objects[1].pos.z,
			sc->objects[1].color.red, sc->objects[1].color.green, sc->objects[1].color.blue);

	SDL_Surface* surfaceMessageObj = TTF_RenderText_Blended(arial, "Object:\n\tType: %d;\n\tPos: x: %f, y: %f, z: %f;\n\tColor: r: %d, g: %d, b: %d;\n", color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_BlitSurface(surfaceMessageObj, &((SDL_Rect){0, 0, surfaceMessageObj->w, surfaceMessageObj->h}),
					sc->sdl->i_surface, &((SDL_Rect){10, surfaceMessage->h + 10 + 10, I_WIDTH, I_HEIGHT}));


	sc->sdl->i_texture = SDL_CreateTextureFromSurface(sc->sdl->i_render, sc->sdl->i_surface); //now you can convert it into a texture
    // SDL_FreeSurface(sc->sdl->i_surface);

	

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	// SDL_RenderCopy(sc->sdl->i_render, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	// SDL_SetRenderDrawColor(sc->sdl->i_render, 0, 0, 0, 0);
	i_sdl_draw(sc);

	// SDL_RenderClear(sc->sdl->i_render);

	/* Use TTF textures. */
	// SDL_RenderCopy(sc->sdl->i_render, sc->sdl->i_texture, NULL, NULL);
	// SDL_RenderPresent(sc->sdl->i_render);
	//Don't forget too free your surface and texture
}

void	i_sdl_init(t_scene *sc)
{
	sc->sdl->i_pixel = (Uint32 *)ft_memalloc(sizeof(Uint32) * I_HEIGHT * I_WIDTH);
	// if (SDL_Init(SDL_INIT_EVERYTHING))
		// ft_err("SDL init error", 1);
	sc->sdl->i_window = SDL_CreateWindow("info", 10, 40, I_WIDTH, I_HEIGHT, SDL_WINDOW_BORDERLESS);
	sc->sdl->i_surface = SDL_CreateRGBSurface(0, I_WIDTH, I_HEIGHT, 32, 0, 0, 0, 0);
	sc->sdl->i_render = SDL_CreateRenderer(sc->sdl->i_window, -1, SDL_RENDERER_SOFTWARE);
	sc->sdl->i_texture = SDL_CreateTexture(sc->sdl->i_render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, I_WIDTH, I_HEIGHT);
	TTF_Init();


	set_background(sc);
	i_sdl_draw(sc);

	// make_text(sc);
	// SDL_LoadBMP
}

void	i_sdl_draw(t_scene *sc)
{
	// SDL_UpdateTexture(sc->sdl->i_texture, NULL, sc->sdl->pixel, I_WIDTH * sizeof(Uint32));
	// SDL_FreeSurface(sc->sdl->i_surface);
	sc->sdl->i_texture = SDL_CreateTextureFromSurface(sc->sdl->i_render, sc->sdl->i_surface);
	SDL_RenderClear(sc->sdl->i_render);
	SDL_RenderCopy(sc->sdl->i_render, sc->sdl->i_texture, NULL, NULL);
	SDL_RenderPresent(sc->sdl->i_render);
}

void	i_sdl_destroy(t_scene *sc)
{
	SDL_DestroyTexture(sc->sdl->i_texture);
	SDL_DestroyRenderer(sc->sdl->i_render);
	SDL_DestroyWindow(sc->sdl->i_window);
}

void	i_sdl_put_pixel(t_scene *sc, int x, int y, int color)
{
	sc->sdl->i_pixel[y * I_WIDTH + x] = color < 0 ? 0 : color;
}
