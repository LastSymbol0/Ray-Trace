/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_sys_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:52:00 by aillia            #+#    #+#             */
/*   Updated: 2019/09/25 17:52:02 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

struct nk_colorf	get_nk_colorf(t_fcolor fcolor, float transparency_coef)
{
	struct nk_colorf res;

	res.r = fcolor.red;
	res.g = fcolor.green;
	res.b = fcolor.blue;
	res.a = transparency_coef;
	return (res);
}

void				set_nk_colorf(struct nk_colorf nk_col, t_obj *obj)
{
	obj->fcolor.red = nk_col.r;
	obj->fcolor.green = nk_col.g;
	obj->fcolor.blue = nk_col.b;
	obj->transparency_coef = nk_col.a;
}

void				nk_exit(struct nk_context *ctx, SDL_Window *win,
												SDL_GLContext gl_context)
{
	nk_clear(ctx);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	nk_sdl_shutdown();
	exit(1);
}

void				strange_fonts_magic(struct nk_context *ctx)
{
	struct nk_font_atlas	*atlas;
	struct nk_font			*droid;
	struct nk_font			*roboto;
	struct nk_font			*future;
	struct nk_font			*cousine;

	nk_sdl_font_stash_begin(&atlas);
	droid = nk_font_atlas_add_from_file(atlas,
					"./nuklear/extra_font/DroidSans.ttf", 14, 0);
	roboto = nk_font_atlas_add_from_file(atlas,
					"./nuklear/extra_font/Roboto-Regular.ttf", 16, 0);
	future = nk_font_atlas_add_from_file(atlas,
			"./nuklear/extra_font/kenvector_future_thin.ttf", 13, 0);
	cousine = nk_font_atlas_add_from_file(atlas,
					"./nuklear/extra_font/Cousine-Regular.ttf", 13, 0);
	nk_sdl_font_stash_end();
	nk_style_set_font(ctx, &droid->handle);
}
