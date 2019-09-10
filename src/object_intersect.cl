#define PLUS_INTENSE_LIGHT 4.0
#define cl_float3 __float3

enum				e_typeobject
{
					CAM,
					CONE,
					PLANE,
					SPHERE,
					CYLINDER,
					NONE,
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

typedef struct		s_fcolor
{
	float			red;
	float			green;
	float			blue;
}					t_fcolor;

// typedef struct		s_vec
// {
// 	float			x;
// 	float			y;
// 	float			z;
// }					cl_float3;

typedef struct		s_ray
{
	cl_float3		orig;
	cl_float3		dir;
}					t_ray;

typedef struct		s_obj
{
	cl_float3		pos;
	cl_float3		rot;
	int				radius;
	t_color			color;
	t_fcolor		fcolor;
	int				type;
	float			difuse;
	float			reflection_coef;
	float			transparency_coef;


	float			t;
}					t_obj;

typedef struct		s_light
{
	cl_float3		pos;
	float			intensity;
	t_color			color;
	t_fcolor		fcolor;
}					t_light;

typedef struct		s_light_arr
{
	t_light			light;
	float			t;
}					t_light_arr;

typedef struct		s_hit
{
	t_obj			obj;
	cl_float3		pos;
	cl_float3		hit_v;
	cl_float3		hit_v_norm;
	cl_float3		norm;
	float			t;
	global t_obj	*addr_obj;
}					t_hit;

// cl_float3			v_minus(cl_float3v1, cl_float3v2);
// float				dot(cl_float3a, cl_float3b);
// cl_float3			v_add(cl_float3v1, cl_float3v2);
// cl_float3			v_scale(cl_float3v, float n);
// cl_float3			fast_normalize(cl_float3v);
// float				fast_length(cl_float3v);
// cl_float3			v_new(float x, float y, float z);
// cl_float3			cross(cl_float3v1, cl_float3v2);
float				v_cos(cl_float3 v1, cl_float3 v2);

float				LOWER_AND_NOT_0(float a, float b);
float3				vectofloat(cl_float3 vec);
cl_float3			floattovec(float3 f3);
float				equalizer(float value, float min, float max);
t_fcolor			make_coef_fcolor(t_fcolor fcolor, float k);
t_fcolor			add_fcolor(t_fcolor a, t_fcolor b);
t_fcolor			norme_fcolor(t_fcolor fcolor);

float				sphere_intersect(const t_ray ray, const t_obj sph);
float				cylinder_intersect(const t_ray ray, const t_obj cylinder);
float				cone_intersect(const t_ray ray, const t_obj cone);
float				plane_intersect(const t_ray ray, const t_obj plane);

float				object_intersect(const t_ray ray, const t_obj object);
t_hit				objects_intersect(const t_ray ray, global t_obj *objects, const int obj_count, t_hit prev_hit);

t_fcolor			shadows(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray_arr);
float				objects_intersect_shadows(const t_ray ray, __global t_obj *objects, const int obj_count, float t);
void				set_norm(t_hit *hit);
float				spec(t_hit hit, t_ray light_ray, t_ray ray_arr);
t_ray				get_reflect_ray(t_hit hit);


/*********************************************************************************/
/* Vec */

// float	dot(cl_float3a, cl_float3b)
// {
// 	return (a.x * b.x + a.y * b.y + a.z * b.z);
// }

// cl_float3 v_minus(cl_float3v1, cl_float3v2)
// {
// 	cl_float3res;

// 	res.x = v1.x - v2.x;
// 	res.y = v1.y - v2.y;
// 	res.z = v1.z - v2.z;
// 	return (res);
// }

// cl_float3v_new(float x, float y, float z)
// {
// 	cl_float3v;

// 	v.x = x;
// 	v.y = y;
// 	v.z = z;
// 	return (v);
// }

// cl_float3fast_normalize(cl_float3v)
// {
// 	return (v_scale(v, 1.0 / fast_length(v)));
// }

// float	fast_length(cl_float3v)
// {
// 	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
// }

// cl_float3v_scale(cl_float3v, float n)
// {
// 	v.x *= n;
// 	v.y *= n;
// 	v.z *= n;
// 	return (v);
// }

// cl_float3v_add(cl_float3v1, cl_float3v2)
// {
// 	cl_float3v;

// 	v.x = v1.x + v2.x;
// 	v.y = v1.y + v2.y;
// 	v.z = v1.z + v2.z;
// 	return (v);
// }

// cl_float3cross(cl_float3v1, cl_float3v2)
// {
// 	cl_float3v;

// 	v.x = v1.y * v2.z - v1.z * v2.y;
// 	v.y = v1.z * v2.x - v1.x * v2.z;
// 	v.z = v1.x * v2.y - v1.y * v2.x;
// 	return (v);
// }

float	v_cos(cl_float3 v1, cl_float3 v2)
{
	return(dot(v1, v2) / (fast_length(v1) * fast_length(v2)));
}

/*********************************************************************************/
/* Utils */

float3	vectofloat(cl_float3 vec)
{
	float3 f3;

	f3.x = vec.x;
	f3.y = vec.y;
	f3.z = vec.z;
	return(f3);
}
cl_float3 floattovec(float3 f3)
{
	cl_float3 vec;

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

t_fcolor			make_coef_fcolor(t_fcolor fcolor, float k)
{
	fcolor.red *= k;
	fcolor.green *= k;
	fcolor.blue *= k;

	return (fcolor);
}

t_fcolor			add_fcolor(t_fcolor a, t_fcolor b)
{
	a.red += b.red;
	a.green += b.green;
	a.blue += b.blue;
	
	return (a);
}

t_fcolor			norme_fcolor(t_fcolor fcolor)
{
	fcolor.red = equalizer(fcolor.red, 0.0, 1.0);
	fcolor.green = equalizer(fcolor.green, 0.0, 1.0);
	fcolor.blue = equalizer(fcolor.blue, 0.0, 1.0);
	return (fcolor);
}

/*********************************************************************************/
/* Objects intersect */

/*
**	Sphere
*/
float				sphere_intersect(const t_ray ray, const t_obj sph)
{
	cl_float3 l;
	cl_float3 pc;
	// cl_float3hit;
	float	dist;
	float	di1;

	l = sph.pos - ray.orig;
	if (dot(ray.dir, l) < 0)
	{
		if (fast_length(l) > sph.radius)
			return (-1);
		if (fast_length(l) == sph.radius)
			return (fast_length(l));
		else
		{
			pc = ray.orig + (ray.dir * dot(ray.dir, l));
			dist = sqrt(pow((float)sph.radius, (float)2) - pow((float)fast_length(pc - sph.pos), (float)2));
			di1 = dist - fast_length(pc - ray.orig);
			// hit = v_add(ray.orig, v_scale(ray.dir, di1));
			return (di1);
		}
	}
	else
	{
		pc = ray.orig + (ray.dir * dot(ray.dir, l));
		if (fast_length(sph.pos - pc) > sph.radius)
			return (-1);
		dist = sqrt(pow((float)sph.radius, (float)2) - pow((float)fast_length(pc - sph.pos), (float)2));
		if (fast_length(l) > sph.radius)
			di1 = fast_length(pc - ray.orig) - dist;
		else
			di1 = fast_length(pc - ray.orig) + dist;
			return (di1);
	}
}

/*
**	Cylinder
*/
float				cylinder_intersect(const t_ray ray, const t_obj cylinder)
{
	cl_float3 l;
	t_eq	eq;
	float	t1;
	float	t2;

	l = ray.orig - cylinder.pos;
	eq.a = dot(ray.dir, ray.dir) - pow((float)dot(ray.dir, cylinder.rot), (float)2);
	eq.b = 2 * (dot(ray.dir, l) - dot(ray.dir, cylinder.rot) * dot(l, cylinder.rot));
	eq.c = dot(l, l) - pow((float)dot(l, cylinder.rot), (float)2) -	pow((float)cylinder.radius, (float)2);
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
	cl_float3 l;
	t_eq	eq;
	float	t1;
	float	t2;

	l = ray.orig - cone.pos;
	eq.a = dot(ray.dir, ray.dir) - (CONE_COEF + pow((float)cone.radius, (float)2)) * pow((float)dot(ray.dir, cone.rot), (float)2);
	eq.b = 2 * (dot(ray.dir, l) - (CONE_COEF + pow((float)cone.radius, (float)2)) * dot(ray.dir, cone.rot) * dot(l, cone.rot));
	eq.c = dot(l, l) - (CONE_COEF + pow((float)cone.radius, (float)2)) * pow((float)dot(l, cone.rot), (float)     2);
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
	cl_float3 l;
	float	dist;

	l = ray.orig - plane.pos;
	dist = (((dot(plane.rot, plane.pos) - dot(plane.rot, ray.orig)) / dot(ray.dir, plane.rot)));
	return (dist);
}

/*********************************************************************************/
/* Main shit */

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

void					set_norm(t_hit *hit)
{
	cl_float3 buf;

	if (hit->obj.type == SPHERE)
		hit->norm = fast_normalize(hit->pos - hit->obj.pos);
	else if (hit->obj.type == PLANE)
		hit->norm = hit->obj.rot;
	else if (hit->obj.type == CYLINDER)
		hit->norm = fast_normalize(cross(cross(hit->obj.rot, hit->pos - hit->obj.pos), hit->obj.rot));
	else if (hit->obj.type == CONE)
	{
		buf = hit->pos - hit->obj.pos;
		if (v_cos(buf, hit->obj.rot) < 0)
			hit->norm = fast_normalize(cross(cross((hit->obj.rot * -1), buf), buf));
		else
			hit->norm = fast_normalize(cross(cross(hit->obj.rot, buf), buf));
	} 
}

t_hit					objects_intersect(const t_ray ray, __global t_obj *objects, const int obj_count, t_hit prev_hit)
{
	int		i;
	float	t;
	float	tmp;
	t_hit hit;

	hit.obj.type = NONE;
	i = -1;
	t = 2147483647;
	while (++i < obj_count)
	{
		if ((tmp = object_intersect(ray, objects[i])) > 0 && tmp < t && &objects[i] != prev_hit.addr_obj)
		{
			t = tmp;
			hit.obj = objects[i];
			hit.addr_obj = &objects[i];
		}
	}
	if (hit.obj.type == NONE)
		return (hit);
	hit.pos = (ray.dir * t) + ray.orig;
	t += 1;
	hit.hit_v = hit.pos - ray.dir / 10;
	hit.t = t;
	hit.hit_v_norm = ray.dir;
	set_norm(&hit);
	return (hit);
}

float			spec(t_hit hit, t_ray light_ray, t_ray ray_arr)
{
	cl_float3	spec_ray;

	spec_ray = light_ray.dir - (2 * hit.norm * dot(light_ray.dir, hit.norm));
	return (equalizer(pown(v_cos(spec_ray, fast_normalize(ray_arr.orig - hit.pos)), 20), 0., 1.));
}

t_ray			get_reflect_ray(t_hit hit)
{
	t_ray	reflect_ray;

	reflect_ray.dir = normalize(hit.hit_v_norm - (2 * hit.norm * dot(hit.hit_v_norm, hit.norm)));
	reflect_ray.orig = hit.hit_v;
	return (reflect_ray);
}

float				objects_intersect_shadows(const t_ray ray, __global t_obj *objects, const int obj_count, float t)
{
	int		i;
	float	tmp;

	i = -1;
	while (++i < obj_count)
		if ((tmp = object_intersect(ray, objects[i])) > 0 && tmp < t)
		{
			t = tmp;
			// if (objects[i].transparency_coef != 0.)
			// {

			// }
		}
	return (t);
}

t_fcolor			shadows(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray)
{
	int				i;
	float			t;
	float			buf;
	float			sum[5];
	t_hit			new_hit;
	t_fcolor		res;
	t_ray			light_ray;
	cl_float3		rev_light_dir;
	// float			p;

	sum[0] = 0;
	sum[1] = 0;
	sum[2] = 0;
	sum[3] = ambient / 100.;
	i = -1;
	while (++i < light_count)
	{
		light_ray.orig = light[i].pos;
		light_ray.dir = hit.pos - light[i].pos;
		t = fast_length(light_ray.dir) - 0.1;
		light_ray.dir = fast_normalize(light_ray.dir);

		new_hit = objects_intersect(light_ray, obj, obj_count, hit);
		buf = fabs(t - new_hit.t);
		// buf = fabs(t - objects_intersect_shadows(light_ray, obj, obj_count, t));
		if (t < new_hit.t || new_hit.obj.transparency_coef != 0.)
		{
			sum[3] = ambient / 100.;
			rev_light_dir = light_ray.dir * -1;
			// difuse coef
			sum[3] += equalizer((light[i].intensity / 100) * hit.obj.difuse * pown(dot(rev_light_dir, hit.norm) / (fast_length(rev_light_dir) * fast_length(hit.norm)), 1), 0.0, 100.);
			// specularity coef
			sum[3] += spec(hit, light_ray, ray);
			// distanse coef
			sum[3] = equalizer(sum[3] * PLUS_INTENSE_LIGHT * equalizer(1.0 / sqrt(t), 0.0, 1.0), ambient / 100., 1.0);

			// drugoi distanse coef
			// sum[3] = sum[3] * (1.0/(sqrt(t)));
			//	printf("equ = %f\n", sum[3]);

			sum[0] += light[i].fcolor.red * hit.obj.fcolor.red * sum[3];
			sum[1] += light[i].fcolor.green * hit.obj.fcolor.green * sum[3];
			sum[2] += light[i].fcolor.blue * hit.obj.fcolor.blue * sum[3];

			if (t >= new_hit.t && new_hit.obj.transparency_coef != 0.)
			{
				sum[0] *= new_hit.obj.transparency_coef;
				sum[1] *= new_hit.obj.transparency_coef;
				sum[2] *= new_hit.obj.transparency_coef;

				// sum[0] += new_hit.obj.fcolor.red * (1 - new_hit.obj.transparency_coef) / 10;
				// sum[1] += new_hit.obj.fcolor.green * (1 - new_hit.obj.transparency_coef) / 10;
				// sum[2] += new_hit.obj.fcolor.blue * (1 - new_hit.obj.transparency_coef) / 10;
			}
			// sum[0] += (((light[i].color.red / 255.0) * (hit.obj.color.red / 255.0))) * sum[3];
			// sum[1] += (((light[i].color.green / 255.0) * (hit.obj.color.green / 255.0))) * sum[3];
			// sum[2] += (((light[i].color.blue / 255.0) * (hit.obj.color.blue / 255.0))) * sum[3];
		}
	}

	sum[4] = ambient / 100.;
	sum[0] < ((hit.obj.fcolor.red) * sum[4]) ? sum[0] = ((hit.obj.fcolor.red) * sum[4]) : 0;
	sum[1] < ((hit.obj.fcolor.green) * sum[4]) ? sum[1] = ((hit.obj.fcolor.green) * sum[4]) : 0;
	sum[2] < ((hit.obj.fcolor.blue) * sum[4]) ? sum[2] = ((hit.obj.fcolor.blue) * sum[4]) : 0;

	res.red = equalizer(sum[0], 0.0, 1.0);
	res.green = equalizer(sum[1], 0.0, 1.0);
	res.blue = equalizer(sum[2], 0.0, 1.0);

	// res = make_coef_fcolor(res, 1 - hit.obj.transparency_coef);

	// final color
	return (res);
}

t_fcolor			refcletions(t_fcolor prev_fcolor, __global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray)
{
	t_fcolor	res_fcolor;
	int			reflection_count;
	float		reflection_intens;
	int			max_reflections = 1;

	if (hit.obj.reflection_coef == 0.)
		return (prev_fcolor);
	res_fcolor = make_coef_fcolor(prev_fcolor, 1 - hit.obj.reflection_coef);
	while (max_reflections-- != 0 && hit.obj.type != NONE && hit.obj.reflection_coef != 0.)
	{
		reflection_intens = hit.obj.reflection_coef;
		ray = get_reflect_ray(hit);
		hit = objects_intersect(ray, obj, obj_count, hit);
		// return(shadows(obj, obj_count, light, light_count, hit, ambient, ray));
		// if (hit.obj.type == NONE || hit.obj.reflection_count == 0)
			// break ;
		res_fcolor = add_fcolor(res_fcolor, make_coef_fcolor(shadows(obj, obj_count, light, light_count, hit, ambient, ray), reflection_intens * (1 - hit.obj.transparency_coef)));
		// res_fcolor = shadows(obj, obj_count, light, light_count, hit, ambient, ray);
	}
	return (norme_fcolor(res_fcolor));
}

t_fcolor			transparency(t_fcolor prev_fcolor, __global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray)
{
	t_fcolor	res_fcolor;
	float		transparency_coef;

	if (hit.obj.transparency_coef <= 0.)
		return (prev_fcolor);
	res_fcolor = make_coef_fcolor(prev_fcolor, 1 - hit.obj.transparency_coef);
	while (hit.obj.type != NONE && hit.obj.transparency_coef != 0.)
	{
		transparency_coef = hit.obj.transparency_coef;
		ray.orig = hit.pos;
		hit = objects_intersect(ray, obj, obj_count, hit);
		res_fcolor = add_fcolor(res_fcolor, make_coef_fcolor(shadows(obj, obj_count, light, light_count, hit, ambient, ray), transparency_coef));
	}
	return (norme_fcolor(res_fcolor));
}

int					color(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray)
{
	t_fcolor	fcolor;
	
	fcolor = shadows(obj, obj_count, light, light_count, hit, ambient, ray);
	fcolor = transparency(fcolor, obj, obj_count, light, light_count, hit, ambient, ray);
	fcolor = refcletions(fcolor, obj, obj_count, light, light_count, hit, ambient, ray);
	return (((int)(fcolor.red * 255)  << 16) | (((int)(fcolor.green * 255)) << 8) | (int)(fcolor.blue * 255));
}

__kernel void		ray_cast(__global t_ray *ray_arr, __global t_obj *objects, __global t_light *light, const int obj_count, __global unsigned int *pixels, const int light_count, const float ambient)
{
	int		i;
	t_hit 	hit;

	i = get_global_id(0);
	hit.addr_obj = 0;
	hit = objects_intersect(ray_arr[i], objects, obj_count, hit);
	if (hit.obj.type != NONE)
	{
		pixels[i] = color(objects, obj_count, light, light_count, hit, ambient, ray_arr[i]);
	}
	else 
		pixels[i] = 0;
}
