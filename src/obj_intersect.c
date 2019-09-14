/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:56:24 by aillia            #+#    #+#             */
/*   Updated: 2019/09/14 18:56:29 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"
/*********************************************************************************/
/* Objects intersect */

/*
**	Sphere
*/
float				sphere_intersect(const t_ray ray, const t_obj sph)
{
	cl_float3	l;
	cl_float3	pc;
	// cl_float3	hit;
	float	dist;
	float	di1;

	l = v_minus(sph.pos, ray.orig);
	if (v_dot(ray.dir, l) < 0)
	{
		if (v_magn(l) > sph.radius)
			return (-1);
		if (v_magn(l) == sph.radius)
			return(v_magn(l));
		else
		{
			pc = v_add(ray.orig, (v_scale(ray.dir, v_dot(ray.dir, l))));
			dist = sqrt(pow((float)sph.radius, (float)2) - pow((float)v_magn(v_minus(pc, sph.pos)), (float)2));
			di1 = dist - v_magn(v_minus(pc, ray.orig));
			// hit = v_add(ray.orig, v_scale(ray.dir, di1));
			return (di1);
		}
	}
	else
	{
		pc = v_add(ray.orig, (v_scale(ray.dir, v_dot(ray.dir, l))));
		if (v_magn(v_minus(sph.pos, pc)) > sph.radius)
			return (-1);
		dist = sqrt(pow((float)sph.radius, (float)2) - pow((float)v_magn(v_minus(pc, sph.pos)), (float)2));
		if (v_magn(l) > sph.radius)
			di1 = v_magn(v_minus(pc, ray.orig)) - dist;
		else
			di1 = v_magn(v_minus(pc, ray.orig)) + dist;
			return (di1);
	}
}

/*
**	Cylinder
*/
float				cylinder_intersect(const t_ray ray, const t_obj cylinder)
{
	cl_float3	l;
	t_eq	eq;
	float	t1;
	float	t2;

	l = v_minus(ray.orig, cylinder.pos);
	eq.a = v_dot(ray.dir, ray.dir) - pow((float)v_dot(ray.dir, cylinder.rot), (float)2);
	eq.b = 2 * (v_dot(ray.dir, l) - v_dot(ray.dir, cylinder.rot) * v_dot(l, cylinder.rot));
	eq.c = v_dot(l, l) - pow((float)v_dot(l, cylinder.rot), (float)2) -	pow((float)cylinder.radius, (float)2);
	eq.d = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.d < 0)
		return (-1);
	t1 = (-eq.b - sqrt(eq.d)) / (2 * eq.a);
	t2 = (-eq.b + sqrt(eq.d)) / (2 * eq.a);
	return (LOWER_AND_NOT_0(t1, t2));
}

/*
**
**	Cone
**
*/
# define CONE_COEF 0.1
float				cone_intersect(const t_ray ray, const t_obj cone)
{
	cl_float3	l;
	t_eq	eq;
	float	t1;
	float	t2;

	l = v_minus(ray.orig, cone.pos);
	eq.a = v_dot(ray.dir, ray.dir) - (CONE_COEF + pow((float)cone.radius, (float)2)) * pow((float)v_dot(ray.dir, cone.rot), (float)2);
	eq.b = 2 * (v_dot(ray.dir, l) - (CONE_COEF + pow((float)cone.radius, (float)2)) * v_dot(ray.dir, cone.rot) * v_dot(l, cone.rot));
	eq.c = v_dot(l, l) - (CONE_COEF + pow((float)cone.radius, (float)2)) * pow((float)v_dot(l, cone.rot), (float)     2);
	eq.d = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.d < 0)
		return (-1);
	t1 = (-eq.b - sqrt(eq.d)) / (2 * eq.a);
	t2 = (-eq.b + sqrt(eq.d)) / (2 * eq.a);
	return (LOWER_AND_NOT_0(t1, t2));
}

/*
**	Plane
*/
float				plane_intersect(const t_ray ray, const t_obj plane)
{
	cl_float3	l;
	float	dist;

	l = v_minus(ray.orig, plane.pos);
	dist = (((v_dot(plane.rot, plane.pos) - v_dot(plane.rot, ray.orig)) / v_dot(ray.dir, plane.rot)));
	return (dist);
}
