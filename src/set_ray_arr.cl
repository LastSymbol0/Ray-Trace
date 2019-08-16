typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

t_vec	v_add(t_vec v1, t_vec v2);
t_vec	v_scale(t_vec v, float n);
t_vec	v_norm(t_vec v);
float	v_magn(t_vec v);
t_vec	v_new(float x, float y, float z);

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

__kernel void	set_ray_arr(__global int *x, __global int *y, __global t_vec *cam_rot, __global t_vec *dir)
{
	__local float	fov;
	__local float	x1;
	__local float	y1;

	fov = M_PI_2_F;
	x1 = (2 * (*x + 0.5) / (float)24 - 1) * tan(fov / 2) * (float)24 / (float)42;
	y1 = -(2 * (*y + 0.5) / (float)42 - 1) * tan(fov / 2);
	*dir = v_norm(v_add(v_new(x1, y1, 0), *cam_rot));
	dir[1].x = *x;
	dir[1].y = *y;
}

