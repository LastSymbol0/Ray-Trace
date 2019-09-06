/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RT.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 15:11:50 by aillia            #+#    #+#             */
/*   Updated: 2019/09/03 15:13:53 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft/libft.h"
# include "libxml2/libxml/parser.h"
# include "libxml2/libxml/tree.h"
# include <SDL2/SDL.h>
# include <OpenCL/opencl.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <pthread.h>


# define WIDTH sc->width
# define HEIGHT sc->height
# define RAY_ARR sc->ray_arr
# define OCL sc->ocl
# define CL_SUCCES 0
# define OBJECTS_BUFF OCL[1].output[0]
# define RAY_ARR_BUFF OCL[1].output[1]
# define PIXELS_BUFF OCL[1].output[2]
# define LIGHT_BUFF OCL[1].output[3]
# define AMBIENT_BUFF OCL[1].output[4]

# define MAX_OBJ_COUNT 50

# define LOWER_THEN_1(a) (((a) < 1) ? (a) : 1)


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

typedef struct	s_fcolor
{
	float		red;
	float		green;
	float		blue;
}				t_fcolor;

typedef struct	s_ray
{
	cl_float3	orig;
	cl_float3	dir;
}				t_ray;

typedef struct	s_light
{
	cl_float3	pos;
	float		intensity;
	t_color		color;
	t_fcolor	fcolor;
}				t_light;

typedef struct	s_obj
{
	cl_float3	pos;
	cl_float3	rot;
	int			radius;
	t_color		color;
	t_fcolor	fcolor;
	int			type;
	float		difuse;
	float		reflection_coef;
	short		reflection_count;

	float		t;
}				t_obj;

typedef struct			s_SDL
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	SDL_Event			event;
	Uint32				*pixel;
}						t_SDL;

typedef struct			s_OpenCL
{
	cl_int				err;     // error code returned from api calls

	size_t				global;  // global domain size for our calculation
	size_t				local;   // local domain size for our calculation

	cl_platform_id		Platform; // OpenCL platform
	cl_device_id		device_id;    // compute device id
	cl_context			context;        // compute context
	cl_command_queue	commands; // compute command queue
	cl_program			ray_arr_program;        // compute program
	cl_program			object_intersect_program;        // compute program
	cl_kernel			ray_arr_kernel;          // compute kernel
	cl_kernel			object_intersect_kernel;          // compute kernel

	cl_mem				*output;
}						t_OpenCL;

typedef struct s_mythread
{
	pthread_t	tid[1];
	clock_t end;
	clock_t start;
	int		die;
}				t_mythread;

typedef struct	s_scene
{
	t_SDL		*sdl;
	t_OpenCL	*ocl;

	t_obj		cam;
	float		ambient;
	int			max_reflections;

	int			obj_count;
	int			light_count;

	t_ray		*ray_arr;
	t_obj		*objects;
	t_light		*lights;

	char		*name;
	int			width;
	int			height;
	t_mythread	thread;
}				t_scene;

int			ft_atoi_base(char *str, int base);

void		test_sdl(t_scene *sc);
t_SDL		*sdl_init(t_scene *sc);
void		sdl_draw(t_scene *sc);
void		sdl_destroy(t_scene *sc);
void		sdl_put_pixel(t_scene *sc, int x, int y, int color);
void saveScreenshotBMP(t_scene *sc);

t_OpenCL	*init_ocl(void);
void		set_ray_arr_ocl(t_scene *sc);
void		ray_arr_build_ocl_source(t_scene *sc, char *KernelSource, char *KernelName);
void		object_intersect_build_ocl_source(t_scene *sc, char *KernelSource, char *KernelName);
float		fequalizer(float value, float min, float max);
int			equalizer(int value, int min, int max);





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
cl_float3	parse_vec(char *s);
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
t_fcolor	get_fcolor(t_color color);
void	pixel_put(int color);
void	ft_err(char *err, int status);
void	set_tabs(int n);
int		arr_len(char **arr);
char	*read_file(char *filename, size_t file_size);

/*
** vec.c & vec2.c
*/
cl_float3		v_minus(cl_float3 v1, cl_float3 v2);
float			v_dot(cl_float3 a, cl_float3 b);
cl_float3		v_new(float x, float y, float z);
cl_float3		v_norm(cl_float3 v);
float			v_magn(cl_float3 v);
cl_float3		v_scale(cl_float3 v, float n);
cl_float3		v_add(cl_float3 v1, cl_float3 v2);
float			v_angle(cl_float3 a, cl_float3 b);

#endif