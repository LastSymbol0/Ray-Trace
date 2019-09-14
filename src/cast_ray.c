/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:45:49 by aillia            #+#    #+#             */
/*   Updated: 2019/09/14 18:45:51 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

cl_float3	v_matrix(cl_float3	ray, cl_float3 rot)
{
	cl_float3	fin;
	cl_float3	buf;

	rot.x = rot.x * M_PI / 180.;
	rot.y = rot.y * M_PI / 180.;
	rot.z = rot.z * M_PI / 180.;
	
	fin.x = ray.x;
	fin.y = ray.y;
	fin.z = ray.z;
	// printf("%f %f\n",sqrt(1 - pow(rot.y, 2)), rot.z);
	if (rot.y > 0.00001)
	{
		fin.y = ray.y * cos(rot.y) - ray.z * sin(rot.y);
		fin.z = ray.y * sin(rot.y) + ray.z * cos(rot.y);
	}
	// printf("%f %f %f\n", fin.x, fin.y, fin.z);
	buf.x = fin.x;
	buf.z = fin.z;
	if (rot.x > 0.00001)
	{
		fin.x = buf.x * cos(rot.x) + buf.z * sin(rot.x);
		fin.z = -buf.x * sin(rot.x) + buf.z * cos(rot.x);
	}
	buf.x = fin.x;
	buf.y = fin.y;
	if (rot.z > 0.00001)
	{
		fin.x = buf.x * cos(rot.z) - buf.y * sin(rot.z);
		fin.y = buf.x * sin(rot.z) + buf.y * cos(rot.z);
	}
	return (fin);
}

t_ray	get_ray(t_scene *sc, int x, int y)
{
	t_ray	ray;
	float	fov;
	float	x1;
	float	y1;

	fov = (M_PI / 4);
	x1 = (2 * (x + 0.5) / (float)WIDTH - 1) * tan(fov / 2) *
					(float)WIDTH / (float)HEIGHT;
	y1 = -(2 * (y + 0.5) / (float)HEIGHT - 1) * tan(fov / 2);
	ray.dir = v_norm(v_matrix(v_norm(v_new(x1, y1, -1)), sc->cam.rot));
	ray.orig = sc->cam.pos;
	return (ray);
}

float				object_intersect(const t_ray ray, const t_obj object)
{
	if (object.type == SPHERE)
		return(sphere_intersect(ray, object));
	else if (object.type == CYLINDER)
		return(cylinder_intersect(ray, object));
	else if (object.type == CONE)
		return(cone_intersect(ray, object));
	else if (object.type == PLANE)
		return(plane_intersect(ray, object));
	return(0);
}

t_obj	cast_ray(t_scene *sc, t_ray ray)
{
	int		i;
	float	t = 2147483647;
	t_obj	obj;
	float	tmp;

	i = -1;
	while (++i < sc->obj_count)
	{
		if ((tmp = object_intersect(ray, sc->objects[i])) > 0 && tmp < t)
		{
			t = tmp;
			obj = sc->objects[i];
		}
	}
	return (obj);
}