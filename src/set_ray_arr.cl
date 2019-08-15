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

__kernel void	set_ray_arr(int width, int height, t_vec cam_rot, __global t_ray *ray_arr)
{
	float	fov;
	int		x;
	int		y;
	float	x1;
	float	y1;

	fov = (width / 960) * (M_PI / 2);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			x1 = (2 * (x + 0.5) / (float)width - 1) * tan(fov / 2) *
							(float)width / (float)height;
			y1 = -(2 * (y + 0.5) / (float)height - 1) * tan(fov / 2);
			ray_arr[x + y * width].dir.x = x1;
			ray_arr[x + y * width].dir.y = y1;
			x++;
		}
		y++;
	}	
}

