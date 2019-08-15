/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RT.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 15:11:50 by aillia            #+#    #+#             */
/*   Updated: 2019/08/13 20:05:52 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft/libft.h"
# include "libxml2/libxml/parser.h"
# include "libxml2/libxml/tree.h"
# include <SDL2/SDL.h>
# include <stdio.h>
# include <math.h>

# define WIDTH sc->width
# define HEIGHT sc->height
# define RAY_ARR sc->ray_arr

# define MAX_OBJ_COUNT 50

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
	t_vec		orig;
	t_vec		dir;
}				t_ray;

typedef struct	s_light
{
	t_vec		pos;
	float		intensity;
	t_color		color;
}				t_light;

typedef struct	s_obj
{
	t_vec		pos;
	t_vec		rot;
	int			radius;
	t_color		color;
	int			type;
}				t_obj;

typedef struct	s_SDL
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Event		event;
	Uint32			*pixel;
}				t_SDL;


typedef struct	s_scene
{
	t_SDL		*sdl;
	t_obj		cam;
	float		ambient;
	int			max_reflections;

	t_ray		*ray_arr;

	t_obj		*objects;
	t_light		*lights;

	char		*name;
	int			width;
	int			height;
}				t_scene;

int			ft_atoi_base(char *str, int base);

void	test_sdl(t_scene *sc);
t_SDL	*sdl_init(t_scene *sc);
void	sdl_draw(t_scene *sc);
void	sdl_destroy(t_scene *sc);
void	sdl_put_pixel(t_scene *sc, int x, int y, int color);



/*
** p_main.c
*/
t_scene	*parser(char *filename);

/*
** p_alloc.c
*/
void	scene_memory_alloc(t_scene *sc, xmlNodePtr root);

/*
** p_utils.c
*/
t_vec	parse_vec(char *s);
t_color	parse_color(char *s);
short	get_type(char *s);
void	recurs(xmlNodePtr node, int n);

/*
** p_set.c
*/
void	set_object(t_scene *sc, xmlNodePtr obj, int i, short type);
void	scene_set_objects(t_scene *sc, xmlNodePtr root);
int		scene_set_cam(t_scene *sc, xmlNodePtr cur);
void	scene_set_lights(t_scene *sc, xmlNodePtr cur);

/*
** utils.c
*/
void	pixel_put(int color);
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