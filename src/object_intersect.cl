enum			e_typeobject
{
	CAM,
	CONE,
	PLANE,
	SPHERE,
	CYLINDER,
};

typedef struct	s_eq
{
	float		a;
	float		b;
	float		c;
	float		d;
}				t_eq;

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

typedef struct	s_obj
{
	t_vec		pos;
	t_vec		rot;
	int			radius;
	t_color		color;
	int			type;

	float		t;
}				t_obj;

t_vec			v_minus(t_vec v1, t_vec v2);
float			v_dot(t_vec a, t_vec b);
t_vec	v_add(t_vec v1, t_vec v2);
t_vec	v_scale(t_vec v, float n);
t_vec	v_norm(t_vec v);
float	v_magn(t_vec v);
t_vec	v_new(float x, float y, float z);

float	LOWER_AND_NOT_0(float a, float b);

float				sphere_intersect(const t_ray ray, const t_obj sph);
float				cylinder_intersect(const t_ray ray, const t_obj cylinder);
float				cone_intersect(const t_ray ray, const t_obj cone);
float				plane_intersect(const t_ray ray, const t_obj plane);
float				object_intersect(const t_ray ray, const t_obj object);
int					objects_intersect(const t_ray ray, global t_obj *objects, const int obj_count);
int					get_color(t_obj obj);






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


float	LOWER_AND_NOT_0(float a, float b)
{
	if (a < b && a > 0)
		return (a);
	if (b > a && b > 0)
		return (b);
	return (-1);
}
/*
**
**	Sphere
**
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
**
**	Cylinder
**
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
**
**	Plane
**
*/
float				plane_intersect(const t_ray ray, const t_obj plane)
{
	t_vec	l;
	float	dist;

	l = v_minus(ray.orig, plane.pos);
	dist = (((v_dot(plane.rot, plane.pos) - v_dot(plane.rot, ray.orig)) / v_dot(ray.dir, plane.rot)));
	return (dist);
}

int		get_color(t_obj obj)
{
	int	color;

	color = 0;
	color += obj.color.blue;
	color += obj.color.green * 255;
	color += obj.color.red  * 255  * 255;
	return (color);
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
	
}

int					objects_intersect(const t_ray ray, __global t_obj *objects, const int obj_count)
{
	int	i;
	int	i_obj;
	float	t;
	float	tmp;

	i = -1;
	i_obj = -1;
	t = 2147483647;
	while (++i < obj_count)
	{
		if ((tmp = object_intersect(ray, objects[i])) > 0 && tmp < t)
		{
			t = tmp;
			i_obj = i;
		}
	}
	if (i_obj == -1)
		return (0);
	return (get_color(objects[i_obj]));
}

__kernel void		ray_cast(__global t_ray *ray_arr, __global t_obj *objects, const int obj_count, __global unsigned int *pixels)
{
	int		i;

	i = get_global_id(0);
	pixels[i] = objects_intersect(ray_arr[i], objects, obj_count);
	pixels[0] = ray_arr[1].orig.x * 2;
	pixels[1] = ray_arr[1].orig.y * 2;
	pixels[2] = ray_arr[1].orig.z * 2;
}