/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace_ocl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:25:28 by aillia            #+#    #+#             */
/*   Updated: 2019/09/25 14:25:30 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	object_intersect_build_ocl_source(t_scene *sc, char *KernelSource, char *KernelName)
{
	// Create the compute program from the source buffer
	OCL[1].object_intersect_program = clCreateProgramWithSource(OCL[1].context, 1,
	(const char **) &KernelSource, NULL, &OCL[1].err);
	if (!OCL[1].object_intersect_program)
	  ft_err("Failed to create compute program", 1);

	// Build the program executable
	OCL[1].err = clBuildProgram(OCL[1].object_intersect_program, 0, NULL, NULL, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS) {
	  size_t len;
	  char buffer[120048];

	  ft_putendl("Failed to build program executable");
	  clGetProgramBuildInfo(OCL[1].object_intersect_program, OCL[1].device_id, CL_PROGRAM_BUILD_LOG,
				  sizeof(buffer), buffer, &len);
	  ft_err(buffer, 1);
	  exit(1);
	}

	// Create the compute kernel in the program
	OCL[1].object_intersect_kernel = clCreateKernel(OCL[1].object_intersect_program, KernelName, &OCL[1].err);
	if (!OCL[1].object_intersect_kernel || OCL[1].err != CL_SUCCESS)
		ft_err("Failed to create compute kernel", 1);
}

void	ray_trace_ocl(t_scene *sc)
{
	object_intersect_build_ocl_source(sc, read_file("src/object_intersect.cl", 65534), "ray_cast");
	OCL[1].output = (cl_mem*)malloc(sizeof(cl_mem) * 5);
	OBJECTS_BUFF = clCreateBuffer(OCL[1].context, CL_MEM_READ_ONLY,
			sizeof(t_obj) * (sc->obj_count), NULL, &OCL[1].err);
	if (!OBJECTS_BUFF || OCL[1].err != CL_SUCCES) 
		ft_err("Failed to allocate device memory1", 1);
	RAY_ARR_BUFF = clCreateBuffer(OCL[1].context, CL_MEM_READ_ONLY,
			sizeof(t_ray) * WIDTH * HEIGHT, NULL, &OCL[1].err);
	if (!RAY_ARR_BUFF || OCL[1].err != CL_SUCCES) 
		ft_err("Failed to allocate device memory2", 1);
	PIXELS_BUFF = clCreateBuffer(OCL[1].context, CL_MEM_WRITE_ONLY,
			sizeof(Uint32) * WIDTH * HEIGHT, NULL, &OCL[1].err);
	if (!PIXELS_BUFF || OCL[1].err != CL_SUCCES) 
		ft_err("Failed to allocate device memory3", 1);
	LIGHT_BUFF = clCreateBuffer(OCL[1].context, CL_MEM_READ_ONLY, sizeof(t_light) * sc->light_count, NULL, &OCL[1].err);
	if (!LIGHT_BUFF || OCL[1].err != CL_SUCCES) 
		ft_err("Failed to allocate device memory4", 1);

	// Transfer the input into device memory
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, OBJECTS_BUFF, CL_TRUE, 0,
			sizeof(t_obj) * (sc->obj_count), sc->objects, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (obj)", 1);
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, RAY_ARR_BUFF, CL_TRUE, 0,
			sizeof(t_ray) * WIDTH * HEIGHT, RAY_ARR, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (ray_arr)", 1);
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, LIGHT_BUFF, CL_TRUE, 0,
			sizeof(t_light) * sc->light_count, sc->lights, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (lights)", 1);
	
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 0, sizeof(cl_mem), &RAY_ARR_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments1", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 1, sizeof(cl_mem), &OBJECTS_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 3, sizeof(int), &sc->obj_count);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 4, sizeof(cl_mem), &PIXELS_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 2, sizeof(cl_mem), &LIGHT_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 5, sizeof(int), &sc->light_count);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 6, sizeof(float), &sc->ambient);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 7, sizeof(float), &sc->max_reflections);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	
	
	OCL[1].global = WIDTH * HEIGHT;
	OCL[1].local = 250;
	OCL[1].err = clEnqueueNDRangeKernel(OCL[1].commands, OCL[1].object_intersect_kernel,
			       1, NULL, &OCL[1].global, &OCL[1].local,
			       0, NULL, NULL);

	OCL[1].err = clFinish(OCL[1].commands);
	if (OCL[1].err != CL_SUCCES)
		ft_err("fuck (OCL Err)\n", 1);

	// Read back the results from the device to verify the output
	OCL[1].err = clEnqueueReadBuffer(OCL[1].commands, PIXELS_BUFF,
				    CL_TRUE, 0, sizeof(Uint32) * WIDTH * HEIGHT,
				    sc->sdl->pixel, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);

}

void	ray_trace_2(t_scene *sc)
{
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, RAY_ARR_BUFF, CL_TRUE, 0,
			sizeof(t_ray) * WIDTH * HEIGHT, RAY_ARR, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (ray_arr)", 1);
	
	// OCL[1].global = WIDTH * HEIGHT;
	// OCL[1].local = 1;
	OCL[1].err = clEnqueueNDRangeKernel(OCL[1].commands, OCL[1].object_intersect_kernel,
			       1, NULL, &OCL[1].global, &OCL[1].local,
			       0, NULL, NULL);

	OCL[1].err = clFinish(OCL[1].commands);
	if (OCL[1].err != CL_SUCCES)
		ft_err("fuck (OCL Err)\n", 1);

	// Read back the results from the device to verify the output
	OCL[1].err = clEnqueueReadBuffer(OCL[1].commands, PIXELS_BUFF,
				    CL_TRUE, 0, sizeof(Uint32) * WIDTH * HEIGHT,
				    sc->sdl->pixel, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);

}

void	ray_trace_3(t_scene *sc)
{
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, OBJECTS_BUFF, CL_TRUE, 0,
			sizeof(t_obj) * (sc->obj_count), sc->objects, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (obj)", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 1, sizeof(cl_mem), &OBJECTS_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	
	// OCL[1].global = WIDTH * HEIGHT;
	// OCL[1].local = 1;
	OCL[1].err = clEnqueueNDRangeKernel(OCL[1].commands, OCL[1].object_intersect_kernel,
			       1, NULL, &OCL[1].global, &OCL[1].local,
			       0, NULL, NULL);

	OCL[1].err = clFinish(OCL[1].commands);
	if (OCL[1].err != CL_SUCCES)
		ft_err("fuck (OCL Err)\n", 1);

	// Read back the results from the device to verify the output
	OCL[1].err = clEnqueueReadBuffer(OCL[1].commands, PIXELS_BUFF,
				    CL_TRUE, 0, sizeof(Uint32) * WIDTH * HEIGHT,
				    sc->sdl->pixel, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);

}

void	ray_trace_4(t_scene *sc)
{
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, RAY_ARR_BUFF, CL_TRUE, 0,
			sizeof(t_ray) * WIDTH * HEIGHT, RAY_ARR, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (ray_arr)", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 6, sizeof(float), &sc->ambient);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err  = clSetKernelArg(OCL[1].object_intersect_kernel, 7, sizeof(float), &sc->max_reflections);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	
	
	// OCL[1].global = WIDTH * HEIGHT;
	// OCL[1].local = 1;
	OCL[1].err = clEnqueueNDRangeKernel(OCL[1].commands, OCL[1].object_intersect_kernel,
			       1, NULL, &OCL[1].global, &OCL[1].local,
			       0, NULL, NULL);

	OCL[1].err = clFinish(OCL[1].commands);
	if (OCL[1].err != CL_SUCCES)
		ft_err("fuck (OCL Err)\n", 1);

	// Read back the results from the device to verify the output
	OCL[1].err = clEnqueueReadBuffer(OCL[1].commands, PIXELS_BUFF,
				    CL_TRUE, 0, sizeof(Uint32) * WIDTH * HEIGHT,
				    sc->sdl->pixel, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);

}