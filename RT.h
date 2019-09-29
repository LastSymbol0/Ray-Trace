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

/*
** nuklear
*/
# define NK_INCLUDE_FIXED_TYPES
# define NK_INCLUDE_STANDARD_IO
# define NK_INCLUDE_STANDARD_VARARGS
# define NK_INCLUDE_DEFAULT_ALLOCATOR
# define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
# define NK_INCLUDE_FONT_BAKING
# define NK_INCLUDE_DEFAULT_FONT
// # define NK_IMPLEMENTATION
// # define NK_SDL_GL2_IMPLEMENTATION
# include <stdint.h>
# include <stdarg.h>
# include <string.h>
# include <assert.h>
# include <limits.h>
# include "nuklear/nuklear.h"
# include "nuklear/demo/sdl_opengl2/nuklear_sdl_gl2.h"


# include "libft/libft.h"
# include "libxml2/libxml/parser.h"
# include "libxml2/libxml/tree.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>
# include "SDL_ttf.h"
# include <OpenCL/opencl.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <pthread.h>

# define WIDTH sc->width
# define HEIGHT sc->height
# define I_OBJ_WIDTH 440
# define I_OBJ_HEIGHT 770
# define RAY_ARR sc->ray_arr
# define OCL sc->ocl
# define OCL_OIK OCL[1].object_intersect_kernel
# define CL_SUCCES 0
# define OBJECTS_BUFF OCL[1].output[0]
# define RAY_ARR_BUFF OCL[1].output[1]
# define PIXELS_BUFF OCL[1].output[2]
# define LIGHT_BUFF OCL[1].output[3]
# define AMBIENT_BUFF OCL[1].output[4]

# define USED_CL_DEVICE CL_DEVICE_TYPE_CPU
# define MAX_OBJ_COUNT 50

# define LOWER_THEN_1(a) (((a) < 1) ? (a) : 1)
# define BIGGER_THEN_0(a) (((a) > 0) ? (a) : 0)
# define LOWER_THEN_1(a) (((a) < 1) ? (a) : 1)
# define FROM_0_TO_1(a) BIGGER_THEN_0(LOWER_THEN_1((a)))
# define LOWER_AND_NOT_0(a, b) ((a) < (b) && a > 0) ? (a) : ((b) < (a) && (b) > 0) ? (b) : -1

# define CLICK_CLACK(a) ((a) == 0 ? (a) = 1 : ((a) = 0))

# define OBJ_TYPES_COUNT 5
enum			e_typeobject
{
	CAM,
	CONE,
	PLANE,
	SPHERE,
	CYLINDER,
};

enum			e_color_mode
{
	COL_RGB,
	COL_HSV
};


typedef struct		s_eq
{
	float			a;
	float			b;
	float			c;
	float			d;
}					t_eq;


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
	float		transparency_coef;
	float		refract_coef;

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

	const char	**obj_types;
	int			mouse_move_enable;

	char		*name;
	int			width;
	int			height;
	t_mythread	thread;
}				t_scene;


/*
** atoi_base.c
*/
int					ft_atoi_base(char *str, int base);

/*
** nk_main.c
*/
void				main_evt(struct nk_context *ctx, SDL_Window *win, SDL_GLContext glContext, t_scene *sc);

/*
** nk_windows.c
*/
void				obj_win(struct nk_context *ctx, t_obj *obj, t_scene *sc);
void				scene_win(struct nk_context *ctx, t_scene *sc);

/*
** nk_widgets.c
*/
void				delete_button(struct nk_context *ctx);
void				float3_combobox_pos(struct nk_context *ctx, cl_float3 *pos);
void				complex_color_combobox(struct nk_context *ctx, t_obj *obj);

/*
** nk_sys_utils.c
*/
struct nk_colorf	get_nk_colorf(t_fcolor fcolor, float transparency_coef);
void				set_nk_colorf(struct nk_colorf nk_col, t_obj *obj);
void				nk_exit(struct nk_context *ctx, SDL_Window *win, SDL_GLContext glContext);
void				strange_fonts_magic(struct nk_context *ctx);

/*
** sdl.c
*/
t_SDL				*sdl_init(t_scene *sc);
void				sdl_draw(t_scene *sc);
void				sdl_destroy(t_scene *sc);
void				sdl_put_pixel(t_scene *sc, int x, int y, int color);

/*
** sdl_screenshot.c
*/
void 				save_screenshot_bmp(t_scene *sc);

/*
** sdl_hook.c
*/
void				hook(t_scene *sc);

/*
** mouse_event.c
*/
t_obj				*mouse_click(t_scene *sc);
void				mouse_move(t_scene *sc, SDL_Event evt);

/*
** key_event.c
*/
void				w_key_event(t_scene *sc);
void				s_key_event(t_scene *sc);

/*
** open_CL.c
*/
t_OpenCL			*init_ocl(void);

/*
** ray_trce_ocl.c
*/
void				object_intersect_build_ocl_source(t_scene *sc, char *KernelSource, char *KernelName);
void				ray_trace_ocl(t_scene *sc);
void				ray_trace_2(t_scene *sc);
void				ray_trace_3(t_scene *sc);
void				ray_trace_4(t_scene *sc);


/*
** set_ray_arr.c
*/
void				ray_arr_build_ocl_source(t_scene *sc, char *KernelSource, char *KernelName);
void				set_ray_arr_ocl(t_scene *sc);
void				set_ray_arr_ocl_2(t_scene *sc);
void				set_ray_arr_ocl_3(t_scene *sc);

/*
** p_main.c
*/
t_scene				*parser(char *filename);

/*
** p_alloc.c
*/
void				scene_memory_alloc(t_scene *sc, xmlNodePtr root);

/*
** p_utils.c
*/
cl_float3			parse_vec(char *s);
t_color				parse_color(char *s);
short				get_type(char *s);
void				recurs(xmlNodePtr node, int n);

/*
** p_set.c
*/
void				set_object(t_scene *sc, xmlNodePtr obj, int i, short type);
void				scene_set_objects(t_scene *sc, xmlNodePtr root);
int					scene_set_cam(t_scene *sc, xmlNodePtr cur);
void				scene_set_lights(t_scene *sc, xmlNodePtr cur);

/*
** utils.c
*/
t_fcolor			get_fcolor(t_color color);
void				ft_err(char *err, int status);
int					arr_len(char **arr);
char				*read_file(char *filename, size_t file_size);
char				*get_string_obj_type(int type);
float				fequalizer(float value, float min, float max);
int					equalizer(int value, int min, int max);
void				redraw_obj(t_scene *sc);
void				redraw_scene(t_scene *sc);
int					fcolor_equal(t_fcolor a, t_fcolor b);
int					float3_equal(cl_float3 a, cl_float3 b);
int					obj_equal(t_obj a, t_obj b);

/*
** vec.c & vec2.c
*/
cl_float3			v_minus(cl_float3 v1, cl_float3 v2);
float				v_dot(cl_float3 a, cl_float3 b);
cl_float3			v_new(float x, float y, float z);
cl_float3			v_norm(cl_float3 v);
float				v_magn(cl_float3 v);
cl_float3			v_scale(cl_float3 v, float n);
cl_float3			v_add(cl_float3 v1, cl_float3 v2);
cl_float3			v_mult(cl_float3 a, cl_float3 b);
float				v_angle(cl_float3 a, cl_float3 b);

/*
** obj_intersect.c
*/
float				sphere_intersect(const t_ray ray, const t_obj sph);
float				cylinder_intersect(const t_ray ray, const t_obj cylinder);
float				cone_intersect(const t_ray ray, const t_obj cone);
float				plane_intersect(const t_ray ray, const t_obj plane);

/*
** cast_ray.c
*/
t_obj				*cast_ray(t_scene *sc, t_ray ray);
t_ray				get_ray(t_scene *sc, int x, int y);

#endif