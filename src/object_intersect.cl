#define PLUS_INTENSE_LIGHT 4.0

enum				e_typeobject
{
<<<<<<< HEAD
					CAM,
					CONE,
					PLANE,
					SPHERE,
					CYLINDER,
					NONE,
=======
	CAM,
	CONE,
	PLANE,
	SPHERE,
	CYLINDER,
	NONE,
>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27
};

typedef struct		s_eq
{
	float			a;
	float			b;
	float			c;
	float			d;
}					t_eq;

typedef struct		s_color
{
	short			red;
	short			green;
	short			blue;
}					t_color;

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct		s_ray
{
	t_vec			orig;
	t_vec			dir;
}					t_ray;

typedef struct		s_obj
{
<<<<<<< HEAD
	t_vec			pos;
	t_vec			rot;
	int				radius;
	t_color			color;
	int				type;
	float			difuse;
=======
	t_vec		pos;
	t_vec		rot;
	int			radius;
	t_color		color;
	int			type;
	float		difuse;
>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27

	float			t;
}					t_obj;

<<<<<<< HEAD
typedef struct		s_light
{
	t_vec			pos;
	float			intensity;
	t_color			color;
}					t_light;
=======
typedef struct	s_light
{
	t_vec		pos;
	float		intensity;
	t_color		color;
}				t_light;

typedef struct s_light_arr
{
	t_light		light;
	float		t;
}				t_light_arr;
typedef struct s_hit
{
	t_obj	obj;
	t_vec	pos;
	t_vec	norm;
}				t_hit;

t_vec			v_minus(t_vec v1, t_vec v2);
float			v_dot(t_vec a, t_vec b);
t_vec	v_add(t_vec v1, t_vec v2);
t_vec	v_scale(t_vec v, float n);
t_vec	v_norm(t_vec v);
float	v_magn(t_vec v);
t_vec	v_new(float x, float y, float z);
>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27

typedef struct		s_light_arr
{
	t_light			light;
	float			t;
}					t_light_arr;

typedef struct		s_hit
{
	t_obj			obj;
	t_vec			pos;
	t_vec			norm;
}					t_hit;

t_vec				v_minus(t_vec v1, t_vec v2);
float				v_dot(t_vec a, t_vec b);
t_vec				v_add(t_vec v1, t_vec v2);
t_vec				v_scale(t_vec v, float n);
t_vec				v_norm(t_vec v);
float				v_magn(t_vec v);
t_vec				v_new(float x, float y, float z);
t_vec				v_cross(t_vec v1, t_vec v2);
float				v_cos(t_vec v1, t_vec v2);

float				LOWER_AND_NOT_0(float a, float b);
float3				vectofloat(t_vec vec);
t_vec				floattovec(float3 f3);
float				equalizer(float value, float min, float max);

float				sphere_intersect(const t_ray ray, const t_obj sph);
float				cylinder_intersect(const t_ray ray, const t_obj cylinder);
float				cone_intersect(const t_ray ray, const t_obj cone);
float				plane_intersect(const t_ray ray, const t_obj plane);
<<<<<<< HEAD

float				object_intersect(const t_ray ray, const t_obj object);
t_hit				objects_intersect(const t_ray ray, global t_obj *objects, const int obj_count);

int					shadows(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray_arr);
float				objects_intersect_shadows(const t_ray ray, __global t_obj *objects, const int obj_count, float t);
void				set_norm(t_hit *hit);
float				spec(t_hit hit, t_ray light_ray, t_ray ray_arr);

=======
float				object_intersect(const t_ray ray, const t_obj object);
t_hit				objects_intersect(const t_ray ray, global t_obj *objects, const int obj_count);
int					get_color(t_obj obj);
int				shadows(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray_arr);
int				sum_light(t_hit hit, t_light_arr *light_arr, const int light_count);
float					objects_intersect_shadows(const t_ray ray, __global t_obj *objects, const int obj_count, float t);
float3	vectofloat(t_vec vec);
t_vec	floattovec(float3 f3);
float	equalizer(float value, float min, float max);
void					set_norm(t_hit *hit);
float	v_cos(t_vec v1, t_vec v2);
float			spec(t_hit hit, t_ray light_ray, t_ray ray_arr);

float	equalizer(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}
>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27

/*********************************************************************************/
/* Vec */

float	v_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	v_minus(t_vec v1, t_vec v2)
{
	t_vec res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vec	v_new(float x, float y, float z)
{
	t_vec v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	v_norm(t_vec v)
{
	return (v_scale(v, 1.0 / v_magn(v)));
}

float	v_magn(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	v_scale(t_vec v, float n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}

t_vec	v_add(t_vec v1, t_vec v2)
{
	t_vec v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vec	v_cross(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}
<<<<<<< HEAD
=======

float	v_cos(t_vec v1, t_vec v2)
{

	return(v_dot(v1, v2) / (v_magn(v1) * v_magn(v2)));
}

float3	vectofloat(t_vec vec)
{
	float3 f3;

	f3.x = vec.x;
	f3.y = vec.y;
	f3.z = vec.z;
	return(f3);
}

t_vec	floattovec(float3 f3)
{
	t_vec	vec;

	vec.x = f3.x;
	vec.y = f3.y;
	vec.z = f3.z;
	return(vec);
}
>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27

float	v_cos(t_vec v1, t_vec v2)
{
	return(v_dot(v1, v2) / (v_magn(v1) * v_magn(v2)));
}

/*********************************************************************************/
/* Utils */

float3	vectofloat(t_vec vec)
{
	float3 f3;

	f3.x = vec.x;
	f3.y = vec.y;
	f3.z = vec.z;
	return(f3);
}
t_vec	floattovec(float3 f3)
{
	t_vec	vec;

	vec.x = f3.x;
	vec.y = f3.y;
	vec.z = f3.z;
	return(vec);
}

float	equalizer(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}
float	LOWER_AND_NOT_0(float a, float b)
{
	if (a < b && a > 0)
		return (a);
	if (b > a && b > 0)
		return (b);
	return (-1);
}

/*********************************************************************************/
/* Objects intersect */

/*
**	Sphere
*/
float				sphere_intersect(const t_ray ray, const t_obj sph)
{
	t_vec	l;
	t_vec	pc;
	// t_vec	hit;
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
	t_vec	l;
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
	t_vec	l;
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
	t_vec	l;
	float	dist;

	l = v_minus(ray.orig, plane.pos);
	dist = (((v_dot(plane.rot, plane.pos) - v_dot(plane.rot, ray.orig)) / v_dot(ray.dir, plane.rot)));
	return (dist);
}

<<<<<<< HEAD
/*********************************************************************************/
/* Main shit */
=======
int		get_color(t_obj obj)
{
	int	color;

	color = 0;
	color = (obj.color.red  << 16) | (obj.color.green << 8) | obj.color.blue;
	return (color);
}
>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27

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
<<<<<<< HEAD
}

void					set_norm(t_hit *hit)
{
	t_vec	buf;

	if (hit->obj.type == SPHERE)
		hit->norm = v_norm(v_minus(hit->pos, hit->obj.pos));
	else if (hit->obj.type == PLANE)
		hit->norm = hit->obj.rot;
	else if (hit->obj.type == CYLINDER)
		hit->norm = v_cross(v_cross(hit->obj.rot, v_minus(hit->pos, hit->obj.pos)), hit->obj.rot);
	else if (hit->obj.type == CONE)
	{
		buf = v_minus(hit->pos, hit->obj.pos);
		if (v_cos(buf, hit->obj.rot) < 0)
			hit->norm = v_cross(v_cross(v_scale(hit->obj.rot, -1), buf), buf);
		else
			hit->norm = v_cross(v_cross(hit->obj.rot, buf), buf);
	}
}

=======
}

void					set_norm(t_hit *hit)
{
	t_vec	buf;
	if (hit->obj.type == SPHERE)
		hit->norm = v_norm(v_minus(hit->pos, hit->obj.pos));
	else if (hit->obj.type == PLANE)
		hit->norm = hit->obj.rot;
	else if (hit->obj.type == CYLINDER)
		hit->norm = v_cross(v_cross(hit->obj.rot, v_minus(hit->pos, hit->obj.pos)), hit->obj.rot);
	else if (hit->obj.type == CONE)
	{
		buf = v_minus(hit->pos, hit->obj.pos);
		if (v_cos(buf, hit->obj.rot) < 0)
			hit->norm = v_cross(v_cross(v_scale(hit->obj.rot, -1), buf), buf);
		else
			hit->norm = v_cross(v_cross(hit->obj.rot, buf), buf);
	}
}

>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27
t_hit					objects_intersect(const t_ray ray, __global t_obj *objects, const int obj_count)
{
	int	i;
	float	t;
	float	tmp;
	t_hit hit;

	hit.obj.type = NONE;
	i = -1;
	t = 2147483647;
	while (++i < obj_count)
	{
		if ((tmp = object_intersect(ray, objects[i])) > 0 && tmp < t)
		{
			t = tmp;
			hit.obj = objects[i];
		}
	}
	if (hit.obj.type == NONE)
		return (hit);
	hit.pos = v_add(v_scale(ray.dir, t), ray.orig);
	set_norm(&hit);
	return (hit);
}

float			spec(t_hit hit, t_ray light_ray, t_ray ray_arr)
{
	t_vec	spec_ray;

	spec_ray = v_add(v_minus(v_scale(hit.norm, v_cos(hit.norm, v_scale(light_ray.dir, -1))), v_scale(light_ray.dir, -1)), hit.norm);
	return(equalizer(pown(v_cos(spec_ray, v_norm(v_minus(ray_arr.orig, hit.pos))), 20), 0., 1.));
}

float				objects_intersect_shadows(const t_ray ray, __global t_obj *objects, const int obj_count, float t)
{
	int		i;
	float	tmp;

	i = -1;
	while (++i < obj_count)
		if ((tmp = object_intersect(ray, objects[i])) > 0 && tmp < t)
			t = tmp;
	return (t);
}

int				shadows(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray_arr)
{
	int				i;
	float			t;
	float			buf;
	float			sum[5];
	t_ray			light_ray;
	t_vec			rev_light_dir;

	sum[0] = 0;
	sum[1] = 0;
	sum[2] = 0;
	sum[3] = ambient / 100.;
	i = -1;
	while (++i < light_count)
	{
		light_ray.orig = light[i].pos;
		light_ray.dir = v_minus(hit.pos, light[i].pos);
		t = v_magn(light_ray.dir) - 1;
		light_ray.dir = v_norm(light_ray.dir);

		buf = fabs(t - objects_intersect_shadows(light_ray, obj, obj_count, t));
		if (buf < 0.000001)
		{
			rev_light_dir = v_scale(light_ray.dir, -1);
			// difuse coef
			sum[3] += (light[i].intensity / 100) * hit.obj.difuse * pown(v_dot(rev_light_dir, hit.norm) / (v_magn(rev_light_dir) * v_magn(hit.norm)), 1);
			// specularity coef
			sum[3] += spec(hit, light_ray, ray_arr);
			// distanse coef
			sum[3] = equalizer(sum[3] * PLUS_INTENSE_LIGHT * equalizer(1.0 / sqrt(t), 0.0, 1.0), 0.0, 1.0);

			// drugoi distanse coef
			// sum[3] = sum[3] * (1.0/(sqrt(t)));
			//	printf("equ = %f\n", sum[3]);

			sum[0] += (((light[i].color.red / 255.0) * (hit.obj.color.red / 255.0))) * sum[3];
			sum[1] += (((light[i].color.green / 255.0) * (hit.obj.color.green / 255.0))) * sum[3];		
			sum[2] += (((light[i].color.blue / 255.0) * (hit.obj.color.blue / 255.0))) * sum[3];
		}
	}
<<<<<<< HEAD

	sum[4] = ambient / 100.;
	sum[0] < ((hit.obj.color.red / 255.0) * sum[4]) ? sum[0] = ((hit.obj.color.red / 255.0) * sum[4]) : 0;
	sum[1] < ((hit.obj.color.green / 255.0) * sum[4]) ? sum[1] = ((hit.obj.color.green / 255.0) * sum[4]) : 0;
	sum[2] < ((hit.obj.color.blue / 255.0) * sum[4]) ? sum[2] = ((hit.obj.color.blue / 255.0) * sum[4]) : 0;

	sum[0] = equalizer(sum[0], 0.0, 1.0);
	sum[1] = equalizer(sum[1], 0.0, 1.0);
	sum[2] = equalizer(sum[2], 0.0, 1.0);

	// final color
	return (((int)(sum[0] * 255)  << 16) | ((int)(sum[1] * 255) << 8) | (int)(sum[2] * 255));
}

=======
	if (i_obj == -1)
		return (hit);
	hit.obj = objects[i_obj];
	hit.pos = v_add(v_scale(ray.dir, t), ray.orig);
	set_norm(&hit);
	return (hit);
}

float				objects_intersect_shadows(const t_ray ray, __global t_obj *objects, const int obj_count, float t)
{
	int	i;
	int	i_obj;
	float	tmp;


	i = -1;
	i_obj = -1;;
	while (++i < obj_count)
	{
		if ((tmp = object_intersect(ray, objects[i])) > 0 && tmp < t)
		{
			t = tmp;
			i_obj = i;
		}
	}
	return (t);
}

int				sum_light(t_hit hit, t_light_arr *light_arr, const int light_count)
{
	int		i = 0;
	int		sum[3];
	int		div_i = 0;

	sum[0] = 0;
	sum[1] = 0;
	sum[2] = 0;

	while (i < light_count)
	{
		printf("light_arr = %f\n",light_arr[i].t);
		if (light_arr[i].t == 0)
		{
			i++;
			continue;
		}
		sum[0] += light_arr[i].light.color.red * (light_arr->t / (float)light_arr->light.intensity);
		sum[1] += light_arr[i].light.color.green * (light_arr->t / (float)light_arr->light.intensity);		
		sum[2] += light_arr[i].light.color.blue * (light_arr->t / (float)light_arr->light.intensity);		
		i++;
		div_i++;
	}
	sum[0] += hit.obj.color.red;
	sum[1] += hit.obj.color.green;
	sum[2] += hit.obj.color.blue;
	div_i++;
	// printf("div_i = %d\n", div_i);
	// printf("light_count = %d\n", light_count);
	sum[0] /= div_i;
	sum[1] /= div_i;
	sum[2] /= div_i;

	return ((sum[0]  << 16) | (sum[1] << 8) | sum[2]);
}

float			spec(t_hit hit, t_ray light_ray, t_ray ray_arr)
{
	t_vec	spec_ray;

	spec_ray = v_add(v_minus(v_scale(hit.norm, v_cos(hit.norm, v_scale(light_ray.dir, -1))), v_scale(light_ray.dir, -1)), hit.norm);
	return(equalizer(pown(v_cos(spec_ray, v_norm(v_minus(ray_arr.orig, hit.pos))), 20), 0., 1.));
}

int				shadows(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray_arr)
{
//	int color = 0;
	int i = 0;
	int j = 0;
	float	t;
	float3	f3;
	float	buf;
	float	sum[5];
	int		div_i = 0;
	t_light_arr light_arr;
	t_ray	light_ray;
	t_vec	rev_light_dir;

	sum[0] = 0;
	sum[1] = 0;
	sum[2] = 0;
	sum[3] = ambient / 100.;

	while (i < light_count)
	{
		light_ray.orig = light[i].pos;
		light_ray.dir = v_minus(hit.pos, light[i].pos);
		f3 = vectofloat(light_ray.dir);
		// printf("length = %f\n", length(f3));
		// printf("dir = %f %f %f\n", light_ray.dir.x, light_ray.dir.y, light_ray.dir.z);
		t = length(f3) - 1;
		light_ray.dir = v_norm(light_ray.dir);
		// printf("t = %f", t);
		// printf("intensity = %f\n", light[i].intensity);
		// printf("funct = %f\n", objects_intersect_shadows(light_ray, obj, obj_count, t));
		buf = fabs(t - objects_intersect_shadows(light_ray, obj, obj_count, t));
		if (buf < 0.000001)
		{
			j++;
			
			// if (hit.obj.type == SPHERE || hit.obj.type == PLANE || hit.obj.type == CYLINDER)
			// {
				rev_light_dir = v_scale(light_ray.dir, -1);
				// if (hit.obj.type == PLANE && v_cos(hit.norm, light_ray.dir) > 0)
				// {
				// 	hit.norm = v_scale(hit.norm, -1)
				// }
				sum[3] += (light[i].intensity / 100) * hit.obj.difuse * pown(v_dot(rev_light_dir, hit.norm) / (v_magn(rev_light_dir) * v_magn(hit.norm)), 1);
				sum[3] += spec(hit, light_ray, ray_arr);
			// }

			// else
			// 	sum[3] += light[i].intensity / 100;
			sum[3] = equalizer(sum[3] * 4.0 * equalizer(1.0 / sqrt(t), 0.0, 1.0), 0.0, 1.0);
			// sum[3] = sum[3] * (1.0/(sqrt(t)));
			//	printf("equ = %f\n", sum[3]);
			sum[0] += (((light[i].color.red / 255.0) * (hit.obj.color.red / 255.0))) * sum[3];
			sum[1] += (((light[i].color.green / 255.0) * (hit.obj.color.green / 255.0))) * sum[3];		
			sum[2] += (((light[i].color.blue / 255.0) * (hit.obj.color.blue / 255.0))) * sum[3];
			if (get_global_id(0) % 2000 == 840 && get_global_id(0) / 2000 == 660)
				printf("sum[3] = %f\n", sum[3]);
		}
		// printf("light_arr1 = %f\ni = %d\n",light_arr.t, i);
		i++;


	}
	sum[4] = ambient / 100.;
	sum[0] < ((hit.obj.color.red / 255.0) * sum[4]) ? sum[0] = ((hit.obj.color.red / 255.0) * sum[4]) : 0;
	sum[1] < ((hit.obj.color.green / 255.0) * sum[4]) ? sum[1] = ((hit.obj.color.green / 255.0) * sum[4]) : 0;
	sum[2] < ((hit.obj.color.blue / 255.0) * sum[4]) ? sum[2] = ((hit.obj.color.blue / 255.0) * sum[4]) : 0;



	// sum[1] = (hit.obj.color.green / 255.0) * sum[3];
	// sum[2] = (hit.obj.color.blue / 255.0) * sum[3];
	sum[0] = equalizer(sum[0], 0.0, 1.0);
	sum[1] = equalizer(sum[1], 0.0, 1.0);
	sum[2] = equalizer(sum[2], 0.0, 1.0);


	// i = 0;
	// while (i < light_count)
	// {
	// 	// printf("light_arr2 = %f\ni = %d\n",light_arr.t, i);
	// 	// if (light_arr[i].t == 0)
	// 	// {
	// 	// 	i++;
	// 	// 	continue;
	// 	// }
	// // 	tab[0] += tab[3] * (obj->col.red / 255) * (light->col.red / 255);
	// // tab[1] += tab[3] * (obj->col.green / 255) * (light->col.green / 255);
	// // tab[2] += tab[3] * (obj->col.blue / 255) * (light->col.blue / 255);
	// 	if ()
	// 	sum[3] += light_arr.light.intensity / 100
	// 	sum[3] = equalizer(sum[3] * 4.0 * equalizer(1.0 / sqrtf(light_arr.t), 0.0, 1.0), 0.0, 1.0);
	// 	sum[0] += (light_arr.light.color.red / 255) * (light_arr.t / (float)light_arr.light.intensity);
	// 	sum[1] += light_arr.light.color.green * (light_arr.t / (float)light_arr.light.intensity);		
	// 	sum[2] += light_arr.light.color.blue * (light_arr.t / (float)light_arr.light.intensity);		
	// 	i++;
	// 	div_i++;
	// }
	// // printf("div_i = %d\n", div_i);
	// // printf("light_count = %d\n", light_count);
	// sum[0] /= div_i;
	// sum[1] /= div_i;
	// sum[2] /= div_i;
	// if (sum[0] != 0 && sum[1] != 0 && sum[2] != 0)
	// {
	// sum[0] += hit.obj.color.red;
	// sum[1] += hit.obj.color.green;
	// sum[2] += hit.obj.color.blue;
	// sum[0] /= 2;
	// sum[1] /= 2;
	// sum[2] /= 2;
	// }

	return (((int)(sum[0] * 255)  << 16) | ((int)(sum[1] * 255) << 8) | (int)(sum[2] * 255));
}

>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27
__kernel void		ray_cast(__global t_ray *ray_arr, __global t_obj *objects, __global t_light *light, const int obj_count, __global unsigned int *pixels, const int light_count, const float ambient)
{
	int		i;
	t_hit 	hit;

	i = get_global_id(0);
	hit = objects_intersect(ray_arr[i], objects, obj_count);
<<<<<<< HEAD
=======
	// printf("intensity1 = %f pos = %f %f %f color = %ds %ds %ds\n", light[0].intensity, light->pos.x, light->pos.y, light->pos.z, light->color.red, light->color.green, light->color.blue);
	// if (i == 5000)
	// {
 	// printf("ambient = %f\n", ambient);
	// }
	pixels[i] = get_color(hit.obj);
>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27
	if (hit.obj.type != NONE)
	{
		pixels[i] = shadows(objects, obj_count, light, light_count, hit, ambient, ray_arr[i]);
	}
	else 
		pixels[i] = 0;
<<<<<<< HEAD
=======
// 	pixels[0] = ray_arr[1].orig.x * 2;
// 	pixels[1] = ray_arr[1].orig.y * 2;
// 	pixels[2] = ray_arr[1].orig.z * 2;
>>>>>>> 6b81a7962715fa6e4ce0b06b2390e849db503d27
}
