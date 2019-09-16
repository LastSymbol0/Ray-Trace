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

void	render_sc_param(t_scene *sc)
{
	TTF_Font* arial = TTF_OpenFont("/Library/Fonts/Arial.ttf", 20);
	SDL_Color color = {255, 116, 0, 0};
	
	sc->sdl->i_offset_x = 20;
	sc->sdl->i_offset_y = 50;
	// set_string(sc, "Type: 2", arial, color);
	// // sc->sdl->i_offset_x += 30;
	// sc->sdl->i_offset_y += 30;
	// set_string(sc, "Pos:\n\t x = 20; y = 30; z = 40", arial, color);

	char s[500];
	sprintf(s, "Scene:\n\n  Camera:\n    Position:\n      x: %.4f,\n      y: %.4f,\n      z: %.4f;\n    Rotation:\n      x: %.4f,\n      y: %.4f,\n      z: %.4f;\n\n  Objects count:  %d\n  Lights count:  %d\n  Max reflections:  %d\n",
			sc->cam.pos.x, sc->cam.pos.y, sc->cam.pos.z,
			sc->cam.rot.x, sc->cam.rot.y, sc->cam.rot.z,
			sc->obj_count,
			sc->light_count,
			sc->max_reflections);
	set_string(sc, s, arial, color);
	i_sdl_draw(sc);

}

void	render_obj_param(t_scene *sc, t_obj obj)
{
	TTF_Font* arial = TTF_OpenFont("/Library/Fonts/Arial.ttf", 20);
	SDL_Color color = {255, 116, 0, 0};
	
	sc->sdl->i_offset_x = 300;
	sc->sdl->i_offset_y = 50;

	char s[500];
	sprintf(s, "Object:\n\n  Type: %s;\n  Radius: %d;\n  Position:\n    x: %.4f,\n    y: %.4f,\n    z: %.4f;\n  Rotation:\n    x: %.4f,\n    y: %.4f,\n    z: %.4f;\n  Color:\n    r: %d,\n    g: %d,\n    b: %d;\n  Difuse:  %.2f\n  Reflection:  %.2f\n  Transparency:  %.2f\n",
			get_string_obj_type(obj.type),
			obj.radius,
			obj.pos.x, obj.pos.y, obj.pos.z,
			obj.rot.x, obj.rot.y, obj.rot.z,
			obj.color.red, obj.color.green, obj.color.blue,
			obj.difuse,
			obj.reflection_coef,
			obj.transparency_coef);
	set_string(sc, s, arial, color);
	i_sdl_draw(sc);

}


void	mouse_click(t_scene *sc)
{
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);
	printf("Click! x: %d, y: %d\n", mouseX, mouseY);
	t_obj obj;
	obj = cast_ray(sc, get_ray(sc, mouseX, mouseY));
	SDL_FreeSurface(sc->sdl->i_surface);
	set_background(sc);
	render_sc_param(sc);
	// TTF_Font* brush_script = TTF_OpenFont("/Library/Fonts/Brush Script.ttf", 28);
	// SDL_Color color = {255, 116, 0, 0};
	// sc->sdl->i_offset_x = 10;
	// sc->sdl->i_offset_y = 10;
	render_obj_param(sc, obj);
	SDL_RaiseWindow(sc->sdl->i_window);
}

void	hook(t_scene *sc)
{
	int running = 1;

	while (running)
	{
		while (!SDL_PollEvent(&sc->sdl->event))
		{
			if (SDL_QUIT == sc->sdl->event.type || SDL_SCANCODE_ESCAPE == sc->sdl->event.key.keysym.scancode)
				running = 0;
			else if (SDL_SCANCODE_SPACE == sc->sdl->event.key.keysym.scancode)
			{
				sc->thread.start = clock();
				printf("cam rot %f %f %f\n", sc->cam.rot.x, sc->cam.rot.y, sc->cam.rot.z);
				printf("cam pos %f %f %f\n",sc->cam.pos.x, sc->cam.pos.y, sc->cam.pos.z);
				sc->cam.pos.z += -1;

				set_ray_arr_ocl_2(sc);
				sc->thread.end = clock();
				ray_trace_2(sc);
				sc->thread.end = clock();
				sdl_draw(sc);
				sc->thread.end = clock();
			}
			else if(SDL_SCANCODE_S == sc->sdl->event.key.keysym.scancode)
			{
				saveScreenshotBMP(sc);
				sc->sdl->event.key.keysym.scancode = SDL_SCANCODE_F;
			}
			else if(SDL_SCANCODE_I == sc->sdl->event.key.keysym.scancode)
			{
				if (sc->sdl->info == 0)
				{
					sc->sdl->info = 1;
					i_sdl_init(sc);
					render_sc_param(sc);
					render_obj_param(sc, sc->objects[1]);
					// i_sdl_draw(sc);
				}
				else
				{
					sc->sdl->info = 0;
					i_sdl_destroy(sc);
				}
				// sc->sdl->event.key.keysym.scancode = SDL_SCANCODE_F;
			}
			else if (sc->sdl->info == 1 && sc->sdl->event.type == SDL_MOUSEBUTTONDOWN)
			{
				mouse_click(sc);
				// sc->sdl->event.type = 0;
				// mousePress(sc->sdl->event.button);
			}
			else if (SDL_SCANCODE_W == sc->sdl->event.key.keysym.scancode)
			{
				sc->thread.start = clock();
				printf("cam rot %f %f %f\n", sc->cam.rot.x, sc->cam.rot.y, sc->cam.rot.z);
				printf("cam pos %f %f %f\n",sc->cam.pos.x, sc->cam.pos.y, sc->cam.pos.z);
				t_ray dir = get_ray(sc, WIDTH / 2, HEIGHT / 2);
				sc->cam.pos = v_add(sc->cam.pos, dir.dir);

				set_ray_arr_ocl_2(sc);
				sc->thread.end = clock();
				ray_trace_2(sc);
				sc->thread.end = clock();
				sdl_draw(sc);
				sc->thread.end = clock();
			}
		}
	}
}