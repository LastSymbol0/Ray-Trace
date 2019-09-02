/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 17:28:37 by aillia            #+#    #+#             */
/*   Updated: 2019/08/29 16:15:29 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_ray_arr(t_scene *sc)
{
	float	fov;
	int		x;
	int		y;
	float	x1;
	float	y1;

	fov = /*(WIDTH / 960) */ (M_PI / 2);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			x1 = (2 * (x + 0.5) / (float)WIDTH - 1) * tan(fov / 2) *
							(float)WIDTH / (float)HEIGHT;
			y1 = -(2 * (y + 0.5) / (float)HEIGHT - 1) * tan(fov / 2);
			RAY_ARR[x + y * WIDTH].dir = v_norm(v_add(v_new(x1, y1, 0), sc->cam.rot));
			RAY_ARR[x + y * WIDTH].orig = sc->cam.pos;
			x++;
		}
		y++;
	}	
}

// /*
// **	Returns -1 if it's no intersection, and color in any other case
// */
// t_obj	*cast_ray(t_scene *sc, t_ray ray, int limit)
// {
// 	int t;
// 	int	i;
// 	t_obj *obj;
// 	cl_mem	objects;

// 	i = -1;
// 	t = limit;
// 	objects = clCreateBuffer(OCL->context, CL_MEM_READ_WRITE,
// 			sizeof(t_obj) * (sc->obj_count), NULL, &OCL->err);
// 	if (!objects || OCL->err != CL_SUCCES) 
// 		ft_err("Failed to allocate device memory", 1);

// 	// Transfer the input into device memory
// 	OCL->err = clEnqueueWriteBuffer(OCL->commands, objects, CL_TRUE, 0,
// 			sizeof(t_obj) * (sc->obj_count), sc->objects, 0, NULL, NULL);
// 	if (OCL->err != CL_SUCCESS)
// 		ft_err("Failed to write to source array (obj)", 1);

// 	OCL->err  = clSetKernelArg(OCL->object_intersect_kernel, 0, sizeof(t_ray), &ray);
// 	if (OCL->err != CL_SUCCESS)
// 		ft_err("Failed to set kernel arguments1", 1);
// 	OCL->err  = clSetKernelArg(OCL->object_intersect_kernel, 1, sizeof(cl_mem), &objects);
// 	if (OCL->err != CL_SUCCESS)
// 		ft_err("Failed to set kernel arguments2", 1);

// 	OCL->global = sc->obj_count;
// 	OCL->local = 1;
// 	OCL->err = clEnqueueNDRangeKernel(OCL->commands, OCL->object_intersect_kernel,
// 			       1, NULL, &OCL->global, &OCL->local,
// 			       0, NULL, NULL);


// 	clFinish(OCL->commands);
// 	// Read back the results from the device to verify the output
// 	OCL->err = clEnqueueReadBuffer(OCL->commands, objects,
// 				    CL_TRUE, 0, sizeof(t_obj) * (sc->obj_count),
// 				    sc->objects, 0, NULL, NULL );
// 	if (OCL->err != CL_SUCCESS)
// 		ft_err("Failed to read output array", 1);

// 	obj = (t_obj *)ft_memalloc(sizeof(t_obj));
// 	while (++i < sc->obj_count)
// 	{
// 		if (sc->objects[i].t < t && sc->objects[i].t > 0)
// 			*obj = sc->objects[i];
// 	}
// 	return (obj);
// }

int		get_color(t_obj *obj)
{
	int	color;

	if (!obj)
		return (0);
	
	color = 0;
	color += obj->color.blue;
	color += obj->color.green * 255;
	color += obj->color.red  * 255  * 255;
	return (color);
}

void	ray_trace(t_scene *sc)
{

	clock_t end, start;
	int running;
	// cl_mem	objects_buff;
	// cl_mem	ray_arr_buff;
	// cl_mem	pixels_buff;
	cl_mem	cl_mem_buf[5];

start = clock();
	object_intersect_build_ocl_source(sc, read_file("src/object_intersect.cl", 65534), "ray_cast");
	running = 1;


	OBJECTS_BUFF = clCreateBuffer(OCL->context, CL_MEM_READ_ONLY,
			sizeof(t_obj) * (sc->obj_count), NULL, &OCL->err);
	if (!OBJECTS_BUFF || OCL->err != CL_SUCCES) 
		ft_err("Failed to allocate device memory1", 1);
	RAY_ARR_BUFF = clCreateBuffer(OCL->context, CL_MEM_READ_ONLY,
			sizeof(t_ray) * WIDTH * HEIGHT, NULL, &OCL->err);
	if (!RAY_ARR_BUFF || OCL->err != CL_SUCCES) 
		ft_err("Failed to allocate device memory2", 1);
	PIXELS_BUFF = clCreateBuffer(OCL->context, CL_MEM_WRITE_ONLY,
			sizeof(Uint32) * WIDTH * HEIGHT, NULL, &OCL->err);
	if (!PIXELS_BUFF || OCL->err != CL_SUCCES) 
		ft_err("Failed to allocate device memory3", 1);
	if (sc->light_count == 0)
	{
		ft_err("add light", 1);
	}
	LIGHT_BUFF = clCreateBuffer(OCL->context, CL_MEM_READ_ONLY, sizeof(t_light) * sc->light_count, NULL, &OCL->err);
	if (!LIGHT_BUFF || OCL->err != CL_SUCCES) 
	{
		printf("%d\n", OCL->err);
		ft_err("Failed to allocate device memory4", 1);
	}
	// AMBIENT_BUFF = clCreateBuffer(OCL->context, CL_MEM_READ_ONLY, sizeof(float), NULL, &OCL->err);
	// if (!LIGHT_BUFF || OCL->err != CL_SUCCES) 
	// {
	// 	printf("%d\n", OCL->err);
	// 	ft_err("Failed to allocate device memory4", 1);
	// }
		
	printf("%lu\n", sizeof(t_light));
	// Transfer the input into device memory
	OCL->err = clEnqueueWriteBuffer(OCL->commands, OBJECTS_BUFF, CL_TRUE, 0,
			sizeof(t_obj) * (sc->obj_count), sc->objects, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array (obj)", 1);
	OCL->err = clEnqueueWriteBuffer(OCL->commands, RAY_ARR_BUFF, CL_TRUE, 0,
			sizeof(t_ray) * WIDTH * HEIGHT, RAY_ARR, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array (obj)", 1);
	OCL->err = clEnqueueWriteBuffer(OCL->commands, LIGHT_BUFF, CL_TRUE, 0,
			sizeof(t_light) * sc->light_count, sc->lights, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array (obj)", 1);

	// OCL->err = clEnqueueWriteBuffer(OCL->commands, AMBIENT_BUFF, CL_TRUE, 0,
	// 		sizeof(float), &sc->ambient, 0, NULL, NULL);
	// if (OCL->err != CL_SUCCESS)
	// 	ft_err("Failed to write to source array (obj)", 1);
	
	OCL->err  = clSetKernelArg(OCL->object_intersect_kernel, 0, sizeof(cl_mem), &RAY_ARR_BUFF);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments1", 1);
	OCL->err  = clSetKernelArg(OCL->object_intersect_kernel, 1, sizeof(cl_mem), &OBJECTS_BUFF);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL->err  = clSetKernelArg(OCL->object_intersect_kernel, 3, sizeof(int), &sc->obj_count);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL->err  = clSetKernelArg(OCL->object_intersect_kernel, 4, sizeof(cl_mem), &PIXELS_BUFF);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL->err  = clSetKernelArg(OCL->object_intersect_kernel, 2, sizeof(cl_mem), &LIGHT_BUFF);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL->err  = clSetKernelArg(OCL->object_intersect_kernel, 5, sizeof(int), &sc->light_count);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL->err  = clSetKernelArg(OCL->object_intersect_kernel, 6, sizeof(float), &sc->ambient);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	
	

	OCL->global = WIDTH * HEIGHT;
	// OCL->global = 1;
	OCL->local = 1;
	OCL->err = clEnqueueNDRangeKernel(OCL->commands, OCL->object_intersect_kernel,
			       1, NULL, &OCL->global, &OCL->local,
			       0, NULL, NULL);

	OCL->err = clFinish(OCL->commands);

	end = clock();
printf("GPU: The above code block was executed in %.4f second(s)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));
	if (OCL->err != CL_SUCCES)
		ft_err("fuck\n", 1);
	// Read back the results from the device to verify the output
	OCL->err = clEnqueueReadBuffer(OCL->commands, PIXELS_BUFF,
				    CL_TRUE, 0, sizeof(Uint32) * WIDTH * HEIGHT,
				    sc->sdl->pixel, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);


	sdl_draw(sc);
	
	while (running)
		while(!SDL_PollEvent (&sc->sdl->event))
			if (SDL_QUIT == sc->sdl->event.type || SDL_SCANCODE_ESCAPE == sc->sdl->event.key.keysym.scancode)
				running = 0;
	sdl_destroy(sc);
}







int		main(int ac, char **av)
{
	t_scene *sc;
	clock_t end, start;
	t_ray *buf;
	int i = 0;
	int j = 0;

	if (ac == 2)
	{
		sc = parser(av[1]);
		sc->sdl = sdl_init(sc);
		// test_sdl(sc);
		OCL = init_ocl();


	start = clock();
		set_ray_arr(sc);
	end = clock();
	printf("CPU: The above code block was executed in %.4f second(s)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));
	buf = (t_ray*)ft_memalloc(sizeof(t_ray) * WIDTH * HEIGHT);
	while (i < WIDTH * HEIGHT)
	{
		buf[i] = RAY_ARR[i];
		i++;
	}
	start = clock();
		set_ray_arr_ocl(sc);
	end = clock();
	printf("GPU: The above code block was executed in %.4f second(s)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		if (buf[i].dir.x == RAY_ARR[i].dir.x && buf[i].dir.y == RAY_ARR[i].dir.y && buf[i].dir.z == RAY_ARR[i].dir.z)
		{
			j++;
			// printf("| %f %f %f / %f %f %f |", buf[i].dir.x, buf[i].dir.y, buf[i].dir.z, RAY_ARR[i].dir.x, RAY_ARR[i].dir.y, RAY_ARR[i].dir.z );
		}
		// else
		// {
		// 	printf("| %f %f %f \\ %f %f %f |", buf[i].dir.x, buf[i].dir.y, buf[i].dir.z, RAY_ARR[i].dir.x, RAY_ARR[i].dir.y, RAY_ARR[i].dir.z);
		// }
		// if (i % HEIGHT == 0)
		// {
		// 	printf("\n");
		// }

		i++;
	}
	printf("\n");
	printf("%d true of %d\n", j, i);
	start = clock();
	ray_trace(sc);
	end = clock();
	printf("GPU: The above code block was executed in %.4f second(s)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));
	}
	else
		write(1, "1 argument plz\n", 15);
	return (0);
}