typedef struct	s_ray
{
	float3		orig;
	float3		dir;
}				t_ray;

float3	v_matrix(float3	ray, float3 rot)
{
	float3	fin;
	float3	buf;

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

__kernel void	set_ray_arr(const int height, const int width, __global float3 *cam_pos, const float3 cam_rot, __global t_ray *results)
{
	float	fov;
	float	x1;
	float	y1;
	int		i;

	i = get_global_id(0);
	fov = M_PI / 4.;
	x1 = (2 * ((i % width) + 0.5) / (float)width - 1) * tan(fov / 2) * (float)width / (float)height;
	y1 = -(2 * ((i / width) + 0.5) / (float)height - 1) * tan(fov / 2);
	results[i].dir = normalize(v_matrix(normalize((float3)(x1, y1, -1)),cam_rot));
	results[i].orig = *cam_pos;
}

