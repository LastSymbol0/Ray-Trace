/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_widgets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:55:46 by aillia            #+#    #+#             */
/*   Updated: 2019/09/25 17:55:49 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	float3_combobox_pos(struct nk_context *ctx, cl_float3 *pos)
{
	char buffer[64];

	sprintf(buffer, "%.2f, %.2f, %.2f", pos->x, pos->y, pos->z);
	if (nk_combo_begin_label(ctx, buffer, nk_vec2(200, 200)))
	{
		nk_layout_row_dynamic(ctx, 25, 1);
		nk_property_float(ctx, "#X:", -1024.0f, &pos->x, 1024.0f, 0.5, 0.5f);
		nk_property_float(ctx, "#Y:", -1024.0f, &pos->y, 1024.0f, 0.5, 0.5f);
		nk_property_float(ctx, "#Z:", -1024.0f, &pos->z, 1024.0f, 0.5, 0.5f);
		nk_combo_end(ctx);
	}
}

void	complex_color_combobox_rgb_h(struct nk_context *ctx,
											struct nk_colorf *combo_color)
{
	combo_color->r = nk_propertyf(ctx, "#R:", 0, combo_color->r,
													1.0f, 0.01f, 0.005f);
	combo_color->g = nk_propertyf(ctx, "#G:", 0, combo_color->g,
													1.0f, 0.01f, 0.005f);
	combo_color->b = nk_propertyf(ctx, "#B:", 0, combo_color->b,
													1.0f, 0.01f, 0.005f);
	combo_color->a = nk_propertyf(ctx, "#A:", 0, combo_color->a,
													1.0f, 0.01f, 0.005f);
}

void	complex_color_combobox_hsva_h(struct nk_context *ctx,
											struct nk_colorf *combo_color)
{
	float	hsva[4];

	nk_colorf_hsva_fv(hsva, *combo_color);
	hsva[0] = nk_propertyf(ctx, "#H:", 0, hsva[0], 1.0f, 0.01f, 0.05f);
	hsva[1] = nk_propertyf(ctx, "#S:", 0, hsva[1], 1.0f, 0.01f, 0.05f);
	hsva[2] = nk_propertyf(ctx, "#V:", 0, hsva[2], 1.0f, 0.01f, 0.05f);
	hsva[3] = nk_propertyf(ctx, "#A:", 0, hsva[3], 1.0f, 0.01f, 0.05f);
	*combo_color = nk_hsva_colorfv(hsva);
}

void	complex_color_combobox(struct nk_context *ctx, t_obj *obj)
{
	static int			col_mode;
	struct nk_colorf	combo_color;

	combo_color = get_nk_colorf(obj->fcolor, obj->transparency_coef);
	if (nk_combo_begin_color(ctx, nk_rgb_cf(combo_color), nk_vec2(200, 400)))
	{
		nk_layout_row_dynamic(ctx, 120, 1);
		combo_color = nk_color_picker(ctx, combo_color, NK_RGBA);
		nk_layout_row_dynamic(ctx, 25, 2);
		col_mode = nk_option_label(ctx, "RGB", col_mode == COL_RGB)
													? COL_RGB : col_mode;
		col_mode = nk_option_label(ctx, "HSV", col_mode == COL_HSV)
													? COL_HSV : col_mode;
		nk_layout_row_dynamic(ctx, 25, 1);
		if (col_mode == COL_RGB)
			complex_color_combobox_rgb_h(ctx, &combo_color);
		else
			complex_color_combobox_hsva_h(ctx, &combo_color);
		nk_combo_end(ctx);
	}
	set_nk_colorf(combo_color, obj);
}
