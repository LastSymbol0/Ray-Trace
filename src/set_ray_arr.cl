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

t_vec	v_matrix(t_vec	ray, t_vec rot)
{
	t_vec	fin;
	t_vec	buf;

	rot.x = rot.x * M_PI / 180.;
	rot.y = rot.y * M_PI / 180.;
	rot.z = rot.z * M_PI / 180.;
	
	fin.x = ray.x;
	fin.y = ray.y;
	fin.z = ray.z;
	// printf("%f %f\n",sqrt(1 - pow(rot.y, 2)), rot.z);
	if (rot.y > 0.00001)
	{
		fin.y = ray.y * cos(rot.y) - ray.z * sin(rot.y);
		fin.z = ray.y * sin(rot.y) + ray.z * cos(rot.y);
	}
	// printf("%f %f %f\n", fin.x, fin.y, fin.z);
	buf.x = fin.x;
	buf.z = fin.z;
	if (rot.x > 0.00001)
	{
		fin.x = buf.x * cos(rot.x) + buf.z * sin(rot.x);
		fin.z = -buf.x * sin(rot.x) + buf.z * cos(rot.x);
	}
	buf.x = fin.x;
	buf.y = fin.y;
	if (rot.z > 0.00001)
	{
		fin.x = buf.x * cos(rot.z) - buf.y * sin(rot.z);
		fin.y = buf.x * sin(rot.z) + buf.y * cos(rot.z);
	}
	return (fin);
}

__kernel void	set_ray_arr(const int height, const int width, __global t_vec *cam_pos, const t_vec cam_rot, __global t_ray *results)
{
	float	fov;
	float	x1;
	float	y1;
	int		i;

	i = get_global_id(0);
	fov = M_PI / 3.;
	x1 = (2 * ((i % width) + 0.5) / (float)width - 1) * tan(fov / 2) * (float)width / (float)height;
	y1 = -(2 * ((i / width) + 0.5) / (float)height - 1) * tan(fov / 2);
	results[i].dir = v_norm(v_matrix(v_norm(v_new(x1, y1, -1)),cam_rot));
	results[i].orig = *cam_pos;
}

