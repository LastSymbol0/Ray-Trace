/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_windows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:58:11 by aillia            #+#    #+#             */
/*   Updated: 2019/09/25 17:58:13 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	scene_win_h(struct nk_context *ctx, t_scene *sc)
{
	nk_layout_row_dynamic(ctx, 30, 2);
	nk_label(ctx, "Cam:", NK_TEXT_CENTERED);
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Position:", NK_TEXT_LEFT);
	float3_combobox_pos(ctx, &sc->cam.pos);
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Rotation:", NK_TEXT_LEFT);
	float3_combobox_pos(ctx, &sc->cam.rot);
	nk_layout_row_dynamic(ctx, 30, 2);
	nk_label(ctx, "Scene:", NK_TEXT_CENTERED);
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Window width:", NK_TEXT_LEFT);
	nk_label(ctx, ft_itoa(WIDTH), NK_TEXT_LEFT);
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Window height:", NK_TEXT_LEFT);
	nk_label(ctx, ft_itoa(HEIGHT), NK_TEXT_LEFT);
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Max reflections count:", NK_TEXT_LEFT);
	nk_slider_int(ctx, 0, &sc->max_reflections, 20, 1);
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Ambient:", NK_TEXT_LEFT);
	nk_slider_float(ctx, 0, &sc->ambient, 1.0f, 0.05f);
	nk_end(ctx);
}

void	scene_win(struct nk_context *ctx, t_scene *sc)
{
	cl_float3	prev_pos;
	cl_float3	prev_rot;
	float		prev_ambient;
	int			prev_max_ref;

	prev_pos = sc->cam.pos;
	prev_rot = sc->cam.rot;
	prev_ambient = sc->ambient;
	prev_max_ref = sc->max_reflections;
	if (nk_begin(ctx, "Scene", nk_rect(10, 360, 420, 340),
		NK_WINDOW_BORDER | NK_WINDOW_SCALABLE))
		scene_win_h(ctx, sc);
	if (!float3_equal(prev_pos, sc->cam.pos) ||
	!float3_equal(prev_rot, sc->cam.rot) || prev_ambient != sc->ambient ||
	prev_max_ref != sc->max_reflections)
		redraw_scene(sc);
}

void	obj_win_h(struct nk_context *ctx, t_obj *obj, t_scene *sc)
{
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Object type:", NK_TEXT_LEFT);
	obj->type = nk_combo(ctx, sc->obj_types,
		OBJ_TYPES_COUNT, obj->type, 25, nk_vec2(120, 200));
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Color: ", NK_TEXT_LEFT);
	complex_color_combobox(ctx, obj);
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Position:", NK_TEXT_LEFT);
	float3_combobox_pos(ctx, &obj->pos);
	nk_layout_row_dynamic(ctx, 20, 2);
	nk_label(ctx, "Rotation:", NK_TEXT_LEFT);
	float3_combobox_pos(ctx, &obj->rot);
	obj->rot = v_norm(obj->rot);
}

void	obj_win(struct nk_context *ctx, t_obj *obj, t_scene *sc)
{
	if (nk_begin(ctx, "Object", nk_rect(10, 10, 420, 340),
		NK_WINDOW_BORDER | NK_WINDOW_SCALABLE))
	{
		obj_win_h(ctx, obj, sc);
		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Radius:", NK_TEXT_LEFT);
		nk_property_int(ctx, "", 0, &obj->radius, 100.0f, 1, 1);
		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Reflection coef:", NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &obj->reflection_coef, 1.0f, 0.05f);
		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Transparency coef:", NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &obj->transparency_coef, 1.0f, 0.05f);
		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Refract coef:", NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &obj->refract_coef, 1.0f, 0.05f);
		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Difuse coef:", NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &obj->difuse, 1.0f, 0.05f);
		nk_layout_row_static(ctx, 30, 180, 1);
		if (nk_button_label(ctx, "Delete object"))
			obj->type = CAM;
		nk_end(ctx);
	}
}
