/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:19:26 by aillia            #+#    #+#             */
/*   Updated: 2019/08/13 20:07:31 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_ray	new_ray(cl_float3 *orig, cl_float3 *dir)
{
	t_ray	ray;

	ray.orig = *orig;
	ray.dir = *dir;
	return (ray);
}

float	v_angle(cl_float3 a, cl_float3 b)
{
	return (v_dot(a, b) / (v_magn(a) * v_magn(b)));
}

float	v_dot(cl_float3 a, cl_float3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

cl_float3	v_minus(cl_float3 v1, cl_float3 v2)
{
	cl_float3 res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

cl_float3	v_new(float x, float y, float z)
{
	cl_float3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
