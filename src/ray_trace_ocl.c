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

void	object_intersect_build_ocl_source(t_scene *sc,
										char *kernel_source, char *kernel_name)
{
	size_t	len;
	char	buffer[120048];

	OCL[1].object_intersect_program = clCreateProgramWithSource(OCL[1].context,
						1, (const char **)&kernel_source, NULL, &OCL[1].err);
	if (!OCL[1].object_intersect_program)
		ft_err("Failed to create compute program", 1);
	OCL[1].err = clBuildProgram(OCL[1].object_intersect_program, 0,
													NULL, NULL, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
	{
		ft_putendl("Failed to build program executable");
		clGetProgramBuildInfo(OCL[1].object_intersect_program,
		OCL[1].device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		ft_err(buffer, 1);
		exit(1);
	}
	OCL[1].object_intersect_kernel =
	clCreateKernel(OCL[1].object_intersect_program, kernel_name, &OCL[1].err);
	if (!OCL[1].object_intersect_kernel || OCL[1].err != CL_SUCCESS)
		ft_err("Failed to create compute kernel", 1);
	free(kernel_source);
}

void	ray_trace_2(t_scene *sc)
{
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, RAY_ARR_BUFF, CL_TRUE,
				0, sizeof(t_ray) * WIDTH * HEIGHT, RAY_ARR, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (ray_arr)", 1);
	OCL[1].err = clEnqueueNDRangeKernel(OCL[1].commands,
	OCL[1].object_intersect_kernel, 1, NULL, &OCL[1].global, &OCL[1].local,
															0, NULL, NULL);
	OCL[1].err = clFinish(OCL[1].commands);
	if (OCL[1].err != CL_SUCCES)
		ft_err("fuck (OCL Err)\n", 1);
	OCL[1].err = clEnqueueReadBuffer(OCL[1].commands, PIXELS_BUFF,
					CL_TRUE, 0, sizeof(Uint32) * WIDTH * HEIGHT,
					sc->sdl->pixel, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);
}

void	ray_trace_3(t_scene *sc)
{
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, OBJECTS_BUFF, CL_TRUE,
			0, sizeof(t_obj) * (sc->obj_count), sc->objects, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (obj)", 1);
	OCL[1].err = clSetKernelArg(OCL[1].object_intersect_kernel, 1,
											sizeof(cl_mem), &OBJECTS_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err = clEnqueueNDRangeKernel(OCL[1].commands,
					OCL[1].object_intersect_kernel,
					1, NULL, &OCL[1].global, &OCL[1].local,
					0, NULL, NULL);
	OCL[1].err = clFinish(OCL[1].commands);
	if (OCL[1].err != CL_SUCCES)
		ft_err("fuck (OCL Err)\n", 1);
	OCL[1].err = clEnqueueReadBuffer(OCL[1].commands, PIXELS_BUFF,
					CL_TRUE, 0, sizeof(Uint32) * WIDTH * HEIGHT,
					sc->sdl->pixel, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);
}

void	ray_trace_4(t_scene *sc)
{
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, RAY_ARR_BUFF, CL_TRUE,
				0, sizeof(t_ray) * WIDTH * HEIGHT, RAY_ARR, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (ray_arr)", 1);
	OCL[1].err = clSetKernelArg(OCL[1].object_intersect_kernel, 6,
												sizeof(float), &sc->ambient);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err = clSetKernelArg(OCL[1].object_intersect_kernel, 7,
										sizeof(float), &sc->max_reflections);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err = clEnqueueNDRangeKernel(OCL[1].commands,
	OCL[1].object_intersect_kernel, 1, NULL, &OCL[1].global, &OCL[1].local,
															0, NULL, NULL);
	OCL[1].err = clFinish(OCL[1].commands);
	if (OCL[1].err != CL_SUCCES)
		ft_err("fuck (OCL Err)\n", 1);
	OCL[1].err = clEnqueueReadBuffer(OCL[1].commands, PIXELS_BUFF,
					CL_TRUE, 0, sizeof(Uint32) * WIDTH * HEIGHT,
					sc->sdl->pixel, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);
}
