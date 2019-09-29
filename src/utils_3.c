/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:27:01 by aillia            #+#    #+#             */
/*   Updated: 2019/09/29 15:27:02 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int		float3_equal(cl_float3 a, cl_float3 b)
{
	if (fabs(a.x - b.x) > 0.0001 ||
		fabs(a.y - b.y) > 0.0001 ||
		fabs(a.z - b.z) > 0.0001)
		return (0);
	return (1);
}

int		obj_equal(t_obj a, t_obj b)
{
	if (a.radius != b.radius)
		return (0);
	if (a.type != b.type)
		return (0);
	if (!fcolor_equal(a.fcolor, b.fcolor))
		return (0);
	if (!float3_equal(a.pos, b.pos))
		return (0);
	if (!float3_equal(a.rot, b.rot))
		return (0);
	if (a.difuse != b.difuse)
		return (0);
	if (a.reflection_coef != b.reflection_coef)
		return (0);
	if (a.transparency_coef != b.transparency_coef)
		return (0);
	if (a.refract_coef != b.refract_coef)
		return (0);
	return (1);
}
