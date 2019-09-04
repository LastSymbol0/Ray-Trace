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
	int				type;
	float			difuse;

	float			t;
}					t_obj;

typedef struct		s_light
{
	cl_float3		pos;
	float			intensity;
	t_color			color;
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
	cl_float3		norm;
}					t_hit;

// cl_float3			v_minus(cl_float3v1, cl_float3v2);
// float				dot(cl_float3a, cl_float3b);
// cl_float3			v_add(cl_float3v1, cl_float3v2);
// cl_float3			v_scale(cl_float3v, float n);
// cl_float3			normalize(cl_float3v);
// float				length(cl_float3v);
// cl_float3			v_new(float x, float y, float z);
// cl_float3			cross(cl_float3v1, cl_float3v2);
float				v_cos(cl_float3 v1, cl_float3 v2);

float				LOWER_AND_NOT_0(float a, float b);
float3				vectofloat(cl_float3 vec);
cl_float3			floattovec(float3 f3);
float				equalizer(float value, float min, float max);

float				sphere_intersect(const t_ray ray, const t_obj sph);
float				cylinder_intersect(const t_ray ray, const t_obj cylinder);
float				cone_intersect(const t_ray ray, const t_obj cone);
float				plane_intersect(const t_ray ray, const t_obj plane);

float				object_intersect(const t_ray ray, const t_obj object);
t_hit				objects_intersect(const t_ray ray, global t_obj *objects, const int obj_count);

int					shadows(__global t_obj *obj, const int obj_count, __global t_light *light, const int light_count, t_hit hit, const float ambient, t_ray ray_arr);
float				objects_intersect_shadows(const t_ray ray, __global t_obj *objects, const int obj_count, float t);
void				set_norm(t_hit *hit);
float				spec(t_hit hit, t_ray light_ray, t_ray ray_arr);


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

// cl_float3normalize(cl_float3v)
// {
// 	return (v_scale(v, 1.0 / length(v)));
// }

// float	length(cl_float3v)
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
	return(dot(v1, v2) / (length(v1) * length(v2)));
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
		if (length(l) > sph.radius)
			return (-1);
		if (length(l) == sph.radius)
			return(length(l));
		else
		{
			pc = ray.orig + (ray.dir * dot(ray.dir, l));
			dist = sqrt(pow((float)sph.radius, (float)2) - pow((float)length(pc - sph.pos), (float)2));
			di1 = dist - length(pc - ray.orig);
			// hit = v_add(ray.orig, v_scale(ray.dir, di1));
			return (di1);
		}
	}
	else
	{
		pc = ray.orig + (ray.dir * dot(ray.dir, l));
		if (length(sph.pos - pc) > sph.radius)
			return (-1);
		dist = sqrt(pow((float)sph.radius, (float)2) - pow((float)length(pc - sph.pos), (float)2));
		if (length(l) > sph.radius)
			di1 = length(pc - ray.orig) - dist;
		else
			di1 = length(pc - ray.orig) + dist;
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
		hit->norm = normalize(hit->pos - hit->obj.pos);
	else if (hit->obj.type == PLANE)
		hit->norm = hit->obj.rot;
	else if (hit->obj.type == CYLINDER)
		hit->norm = cross(cross(hit->obj.rot, hit->pos - hit->obj.pos), hit->obj.rot);
	else if (hit->obj.type == CONE)
	{
		buf = hit->pos - hit->obj.pos;
		if (v_cos(buf, hit->obj.rot) < 0)
			hit->norm = cross(cross((hit->obj.rot * -1), buf), buf);
		else
			hit->norm = cross(cross(hit->obj.rot, buf), buf);
	} 
}

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
			// printf("Хит!");
		}
	}
	if (hit.obj.type == NONE)
		return (hit);
	hit.pos = (ray.dir * t) + ray.orig;
	set_norm(&hit);
	return (hit);
}

float			spec(t_hit hit, t_ray light_ray, t_ray ray_arr)
{
	cl_float3	spec_ray;

	spec_ray = ((hit.norm * v_cos(hit.norm, light_ray.dir * -1)) - light_ray.dir * -1) + hit.norm;
	return (equalizer(pown(v_cos(spec_ray, normalize(ray_arr.orig - hit.pos)), 20), 0., 1.));
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
	cl_float3		rev_light_dir;

	sum[0] = 0;
	sum[1] = 0;
	sum[2] = 0;
	sum[3] = ambient / 100.;
	i = -1;
	while (++i < light_count)
	{
		light_ray.orig = light[i].pos;
		light_ray.dir = hit.pos - light[i].pos;
		t = length(light_ray.dir) - 1;
		light_ray.dir = normalize(light_ray.dir);

		buf = fabs(t - objects_intersect_shadows(light_ray, obj, obj_count, t));
		if (buf < 0.000001)
		{
			rev_light_dir = light_ray.dir * -1;
			// difuse coef
			sum[3] += (light[i].intensity / 100) * hit.obj.difuse * pown(dot(rev_light_dir, hit.norm) / (length(rev_light_dir) * length(hit.norm)), 1);
			// specularity coef
			// sum[3] += spec(hit, light_ray, ray_arr);
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

__kernel void		ray_cast(__global t_ray *ray_arr, __global t_obj *objects, __global t_light *light, const int obj_count, __global unsigned int *pixels, const int light_count, const float ambient)
{
	int		i;
	t_hit 	hit;

	i = get_global_id(0);
	hit = objects_intersect(ray_arr[i], objects, obj_count);
	if (hit.obj.type != NONE)
	{
		pixels[i] = shadows(objects, obj_count, light, light_count, hit, ambient, ray_arr[i]);
	}
	else 
		pixels[i] = 0;
}
