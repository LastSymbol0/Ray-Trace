/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RT.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 15:11:50 by aillia            #+#    #+#             */
/*   Updated: 2019/08/11 15:11:54 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft/libft.h"
# include "libxml2/libxml/parser.h"
# include "libxml2/libxml/tree.h"
# include <stdio.h>

enum			e_typeobject
{
	CAM,
	CONE,
	PLANE,
	SPHERE,
	CYLINDER,
};

typedef struct	s_color
{
	short		red;
	short		green;
	short		blue;
}				t_color;

typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef struct	s_ray
{
	t_vec		*orig;
	t_vec		*dir;
}				t_ray;

typedef struct	s_light
{
	t_vec		pos;
	float		intensity;
	int			inside;
}				t_light;

typedef struct	s_obj
{
	t_vec		pos;
	t_vec		rot;
	int			radius;
	t_color		color;
	int			type;
}				t_obj;

typedef struct	s_scene
{
	t_obj		cam;
	float		ambient;

	t_ray		*ray_arr;

	t_obj		*objects;
	t_light		*light;

	char		*name;
	int			width;
	int			height;
}				t_scene;

int			ft_atoi_base(char *str, int base);


/*
** p_main.c
*/
t_scene	*parser(char *filename);

/*
** p_alloc.c
*/
void	scene_memory_alloc(t_scene *sc, xmlNodePtr root);

/*
** utils.c
*/
void	ft_err(char *err, int status);
void	set_tabs(int n);
int		arr_len(char **arr);

/*
** vec.c & vec2.c
*/
t_vec			v_minus(t_vec v1, t_vec v2);
float			v_dot(t_vec a, t_vec b);
t_vec			v_new(float x, float y, float z);
t_vec			v_norm(t_vec v);
float			v_magn(t_vec v);
t_vec			v_scale(t_vec v, float n);
t_vec			v_add(t_vec v1, t_vec v2);
float			v_angle(t_vec a, t_vec b);

#endif