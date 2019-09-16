/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:31:44 by aillia            #+#    #+#             */
/*   Updated: 2019/08/13 20:06:45 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

cl_float3	v_norm(cl_float3 v)
{
	return (v_scale(v, 1.0 / (v_magn(v) > 0 ? v_magn(v) : 0.0001)));
}

float	v_magn(cl_float3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

cl_float3	v_scale(cl_float3 v, float n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}

cl_float3	v_mult(cl_float3 a, cl_float3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

cl_float3	v_add(cl_float3 v1, cl_float3 v2)
{
	cl_float3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}
