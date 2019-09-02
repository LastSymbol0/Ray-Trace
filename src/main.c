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

void	ray_trace(t_scene *sc)
{
	cl_mem	cl_mem_buf[5];

	object_intersect_build_ocl_source(sc, read_file("src/object_intersect.cl", 65534), "ray_cast");

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
	LIGHT_BUFF = clCreateBuffer(OCL->context, CL_MEM_READ_ONLY, sizeof(t_light) * sc->light_count, NULL, &OCL->err);
	if (!LIGHT_BUFF || OCL->err != CL_SUCCES) 
		ft_err("Failed to allocate device memory4", 1);

	// Transfer the input into device memory
	OCL->err = clEnqueueWriteBuffer(OCL->commands, OBJECTS_BUFF, CL_TRUE, 0,
			sizeof(t_obj) * (sc->obj_count), sc->objects, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array (obj)", 1);
	OCL->err = clEnqueueWriteBuffer(OCL->commands, RAY_ARR_BUFF, CL_TRUE, 0,
			sizeof(t_ray) * WIDTH * HEIGHT, RAY_ARR, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array (ray_arr)", 1);
	OCL->err = clEnqueueWriteBuffer(OCL->commands, LIGHT_BUFF, CL_TRUE, 0,
			sizeof(t_light) * sc->light_count, sc->lights, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array (lights)", 1);
	
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
	if (OCL->err != CL_SUCCES)
		ft_err("fuck (OCL Err)\n", 1);

	// Read back the results from the device to verify the output
	OCL->err = clEnqueueReadBuffer(OCL->commands, PIXELS_BUFF,
				    CL_TRUE, 0, sizeof(Uint32) * WIDTH * HEIGHT,
				    sc->sdl->pixel, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);

}

int		main(int ac, char **av)
{
	t_scene *sc;
	clock_t end, start;
	int running = 1;

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

		start = clock();
			set_ray_arr_ocl(sc);
		end = clock();
		printf("GPU: The above code block was executed in %.4f second(s)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));

		start = clock();
			ray_trace(sc);
		end = clock();
		printf("GPU: The above code block was executed in %.4f second(s)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));

		sdl_draw(sc);
		while (running)
			while(!SDL_PollEvent (&sc->sdl->event))
				if (SDL_QUIT == sc->sdl->event.type || SDL_SCANCODE_ESCAPE == sc->sdl->event.key.keysym.scancode)
					running = 0;
		sdl_destroy(sc);
	}
	else
		write(1, "1 argument plz\n", 15);
	return (0);
}