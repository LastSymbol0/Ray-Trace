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

__kernel void	set_ray_arr(const int height, const int width, const t_vec cam_pos, const t_vec cam_rot, __global t_ray *results)
{
	float	fov;
	float	x1;
	float	y1;
	int		i;

	i = get_global_id(0);
	fov = M_PI_2_F;
	x1 = (2 * ((i % height) + 0.5) / (float)width - 1) * tan(fov / 2) * (float)width / (float)height;
	y1 = -(2 * ((i / height) + 0.5) / (float)height - 1) * tan(fov / 2);
	results[i].dir = v_norm(v_add(v_new(x1, y1, 0), cam_rot));
	results[i].orig = cam_pos;
}

