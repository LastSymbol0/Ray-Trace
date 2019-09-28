#define PLUS_INTENSE_LIGHT 4.0
#define LIMIT 2147483647
#define cl_float3 __float3

#ifndef MAX_QUEUE_SIZE
# define MAX_QUEUE_SIZE 16
#endif

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
	float			refract_coef;


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
	cl_float3		pos_;
	cl_float3		hit_v;
	cl_float3		hit_v_norm;
	cl_float3		norm;
	float			t;
	global t_obj	*addr_obj;
}					t_hit;

typedef struct	s_node
{
	t_hit		hit;
	t_ray		ray;
	t_fcolor	color;
	float		k;
}				t_node;


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
t_fcolor			mult_fcolor(t_fcolor a, t_fcolor b);
t_fcolor			norme_fcolor(t_fcolor fcolor);

float				sphere_intersect(const t_ray ray, const t_obj sph);
float				cylinder_intersect(const t_ray ray, const t_obj cylinder);
float				cone_intersect(const t_ray ray, const t_obj cone);
float				plane_intersect(const t_ray ray, const t_obj plane);

float				object_intersect(const t_ray ray, const t_obj object);
t_hit				objects_intersect(const t_ray ray, global t_obj *objects, const int obj_count, t_hit prev_hit, float t);

t_fcolor			shadows(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray_arr);
float				objects_intersect_shadows(const t_ray ray, __global t_obj *objects, const int obj_count, float t);
void				set_norm(t_hit *hit);
float				spec(t_hit hit, t_ray light_ray, t_ray ray_arr);
t_ray				get_reflect_ray(t_hit hit);

t_fcolor			color_r(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray, int reflection_count);

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

t_fcolor			mult_fcolor(t_fcolor a, t_fcolor b)
{
	a.red *= b.red;
	a.green *= b.green;
	a.blue *= b.blue;

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

t_hit					objects_intersect(const t_ray ray, __global t_obj *objects, const int obj_count, t_hit prev_hit, float t)
{
	int		i;
	float	tmp;
	t_hit hit;

	hit.obj.type = NONE;
	hit.obj.transparency_coef = 0.000000;
	i = -1;
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
	hit.t = t;
	hit.hit_v = hit.pos - ray.dir / 10;
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

float3			get_refract_ray(float3 ray_dir, float3 a_normal, float a_matIOR) 
{
	float eta = 1.0f/a_matIOR; // eta = in_IOR/out_IOR
	float cos_theta = -dot(a_normal, ray_dir);
	if(cos_theta < 0)
	{
	  cos_theta *= -1.0f;
	  a_normal *= -1.0f;
	  eta = 1.0f/eta;
	}
	float k = 1.0f - eta*eta*(1.0-cos_theta*cos_theta);
	if(k >= 0.0f)
	  ray_dir = normalize( eta*ray_dir + (eta*cos_theta - sqrt(k))*a_normal);
	return (ray_dir);

}

t_fcolor			shadows(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray)
{
	int				i;
	float			t;
	float			k;
	t_hit			new_hit;
	t_fcolor		res;
	t_fcolor		tmp[light_count];
	// t_fcolor		res[light_count + 1];
	// t_fcolor		tmp;
	t_ray			light_ray;


			// printf(" %f %f %f ", hit.obj.fcolor.red, hit.obj.fcolor.green, hit.obj.fcolor.blue);
	k = ambient;
	i = -1;
			// res[0].red = 0.;
		// res[0].green = 0.;
		// res[0].blue = 0.;
				// res[1].red = 0.;
		// res[1].green = 0.;
		// res[1].blue = 0.;
		res.red = 0.;
		res.green = 0.;
		res.blue = 0.;	
	while (++i < light_count)
	{
		// res.red = 0.;
		// res.green = 0.;
		// res.blue = 0.;

		light_ray.orig = hit.hit_v;
		light_ray.dir = light[i].pos -  hit.hit_v;
		t = fast_length(light_ray.dir) - 0.1;
		light_ray.dir = fast_normalize(light_ray.dir);

		new_hit.addr_obj = 0;
		new_hit = objects_intersect(light_ray, obj, obj_count, new_hit, t);
		if (new_hit.obj.type == NONE || (new_hit.obj.type != NONE && new_hit.obj.transparency_coef > 0.01))
		{
			k = ambient;
			// difuse coef
			k += equalizer((light[i].intensity / 100) * hit.obj.difuse * pown(dot(light_ray.dir, hit.norm) / (fast_length(light_ray.dir) * fast_length(hit.norm)), 1), 0.0, 100.);
			// specularity coef
			k += spec(hit, light_ray, ray);
			// distanse coef
			k = equalizer(k * PLUS_INTENSE_LIGHT * equalizer(1.0 / sqrt(t), 0.0, 1.0), ambient, 1.0);
			// k = 0.12;
			res = add_fcolor(res, make_coef_fcolor(mult_fcolor(light[i].fcolor, hit.obj.fcolor), k));
			// tmp = res[i];
		}
		if (new_hit.obj.type != NONE && new_hit.obj.transparency_coef > 0.01)
		{
			do
			{
				res = make_coef_fcolor(res, new_hit.obj.transparency_coef);
	
				k = ambient;
				// difuse coef
				k += equalizer((light[i].intensity / 100) * new_hit.obj.difuse * pown(dot(light_ray.dir, new_hit.norm) / (fast_length(light_ray.dir) * fast_length(new_hit.norm)), 1), 0.0, 100.);
				// specularity coef
				k += spec(new_hit, light_ray, ray);
				// distanse coef
				k = equalizer(k * PLUS_INTENSE_LIGHT * equalizer(1.0 / sqrt(t), 0.0, 1.0), ambient, 1.0);
				
				k *= 1 - new_hit.obj.transparency_coef;
	
				res = add_fcolor(res, make_coef_fcolor(mult_fcolor(light[i].fcolor, new_hit.obj.fcolor), k));
	
				light_ray.orig = new_hit.hit_v;
				light_ray.dir = light[i].pos - new_hit.hit_v;
				t = fast_length(light_ray.dir) - 0.1;
				light_ray.dir = fast_normalize(light_ray.dir);
		
				// new_hit.addr_obj = 0;
				new_hit = objects_intersect(light_ray, obj, obj_count, new_hit, t);
			}	while (new_hit.obj.type != NONE && new_hit.obj.transparency_coef > 0.01 && new_hit.addr_obj != hit.addr_obj);
			if (new_hit.obj.type != NONE && new_hit.obj.transparency_coef < 0.01)
			{
				res.red = 0;
				res.green = 0;
				res.blue = 0;
			}
		}
		tmp[i] = res;
	}

	// res.red = 0.;
	// res.green = 0.;
	// res.blue = 0.;
	// i = -1;
	// while (++i < light_count)
	// {
	// 	// printf("%f %f %f", res[i].red, res[i].green, res[i].blue);		
	// 	res = add_fcolor(res, tmp[i]);
	// }
	// printf("\n");
	// res[light_count].red < ((hit.obj.fcolor.red) * ambient) ? res[light_count].red = ((hit.obj.fcolor.red) * ambient) : 0;
	// res[i].green < ((hit.obj.fcolor.green) * ambient) ? res[i].green = ((hit.obj.fcolor.green) * ambient) : 0;
	// res[i].blue < ((hit.obj.fcolor.blue) * ambient) ? res[i].blue = ((hit.obj.fcolor.blue) * ambient) : 0;

	// res[light_count] = norme_fcolor(res[light_count]);

	// final color
	return (res);
}


__kernel void		ray_cast(__global t_ray *ray_arr, __global t_obj *objects, __global t_light *light, const int obj_count, __global unsigned int *pixels, const int light_count, const float ambient, const int max_reflections)
{
	int			i = get_global_id(0);
	t_fcolor	res;
	t_node		my_queue[MAX_QUEUE_SIZE];
	int			cur = 0;
	int			count = 1;
	int			reflection_count = 0;

	// res = {0., 0., 0.};
	res.red = 0.;
	res.green = 0.;
	res.blue = 0.;
	my_queue[cur].ray = ray_arr[i];
	my_queue[cur].hit.addr_obj = 0;
	my_queue[cur].k = 1;
	while (cur < count && count < MAX_QUEUE_SIZE)
	{
		my_queue[cur].hit = objects_intersect(my_queue[cur].ray, objects, obj_count, my_queue[cur].hit, LIMIT);
		if (my_queue[cur].hit.obj.type == NONE)
		{
			cur++;
			continue ;
		}



		if (my_queue[cur].hit.obj.transparency_coef > 0.001)
		{
			my_queue[count].ray.orig = my_queue[cur].hit.hit_v;
			my_queue[count].ray.dir = my_queue[cur].ray.dir;
			my_queue[count].k = my_queue[cur].k * my_queue[cur].hit.obj.transparency_coef;
			my_queue[count].hit.addr_obj = my_queue[cur].hit.addr_obj;
			count++;
		}
		if (my_queue[cur].hit.obj.reflection_coef > 0.001 && reflection_count++ <= max_reflections)
		{
			my_queue[count].ray = get_reflect_ray(my_queue[cur].hit);
			my_queue[count].k = my_queue[cur].k * my_queue[cur].hit.obj.reflection_coef;
			my_queue[count].hit.addr_obj = my_queue[cur].hit.addr_obj;
			count++;
		}

		my_queue[cur].k = my_queue[cur].k * (1. - (my_queue[cur].hit.obj.transparency_coef + my_queue[cur].hit.obj.reflection_coef)); 
		// printf(" %f %f %f \n", my_queue[cur].hit.obj.fcolor.red, my_queue[cur].hit.obj.fcolor.green, my_queue[cur].hit.obj.fcolor.blue);
		my_queue[cur].color = shadows(objects, obj_count, light, light_count, my_queue[cur].hit, ambient, my_queue[cur].ray);

		res = add_fcolor(res, make_coef_fcolor(my_queue[cur].color, my_queue[cur].k));

		cur++;
	}
	res = norme_fcolor(res);
	pixels[i] = ((int)(res.red * 255)  << 16) | (((int)(res.green * 255)) << 8) | (int)(res.blue * 255);
}
