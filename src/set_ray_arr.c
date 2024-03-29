/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:18:25 by aillia            #+#    #+#             */
/*   Updated: 2019/09/25 14:18:28 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	ray_arr_build_ocl_source(t_scene *sc, char *kernel_source,
															char *kernel_name)
{
	size_t	len;
	char	buffer[12048];

	OCL->ray_arr_program = clCreateProgramWithSource(OCL->context, 1,
	(const char **)&kernel_source, NULL, &OCL->err);
	if (!OCL->ray_arr_program)
		ft_err("Failed to create compute program", 1);
	OCL->err = clBuildProgram(OCL->ray_arr_program, 0, NULL, NULL, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
	{
		ft_putendl("Failed to build program executable");
		clGetProgramBuildInfo(OCL->ray_arr_program, OCL->device_id,
		CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		ft_err(buffer, 1);
		exit(1);
	}
	OCL->ray_arr_kernel = clCreateKernel(OCL->ray_arr_program,
													kernel_name, &OCL->err);
	if (!OCL->ray_arr_kernel || OCL->err != CL_SUCCESS)
		ft_err("Failed to create compute kernel", 1);
	free(kernel_source);
}

void	set_ray_arr_ocl_set(t_scene *sc)
{
	OCL->err = clEnqueueWriteBuffer(OCL->commands, OCL->output[1], CL_TRUE, 0,
							sizeof(cl_float3), &sc->cam.pos, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array (ray_arr)", 1);
	OCL->err = clSetKernelArg(OCL->ray_arr_kernel, 0, sizeof(int), &HEIGHT);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err = clSetKernelArg(OCL->ray_arr_kernel, 1, sizeof(int), &WIDTH);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err = clSetKernelArg(OCL->ray_arr_kernel, 2,
											sizeof(cl_mem), &OCL->output[1]);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err = clSetKernelArg(OCL->ray_arr_kernel, 3,
											sizeof(cl_float3), &sc->cam.rot);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err = clSetKernelArg(OCL->ray_arr_kernel, 4,
												sizeof(cl_mem), OCL->output);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
}

void	set_ray_arr_ocl(t_scene *sc)
{
	char	*kernel_source;

	OCL->output = (cl_mem*)malloc(sizeof(cl_mem) * 2);
	kernel_source = read_file("src/set_ray_arr.cl", 5508);
	ray_arr_build_ocl_source(sc, kernel_source, "set_ray_arr");
	*OCL->output = clCreateBuffer(OCL->context, CL_MEM_WRITE_ONLY,
			sizeof(t_ray) * WIDTH * HEIGHT, NULL, &OCL->err);
	if (!OCL->output || OCL->err != CL_SUCCES)
		ft_err("Failed to allocate device memory", 1);
	OCL->output[1] = clCreateBuffer(OCL->context, CL_MEM_READ_ONLY,
			sizeof(cl_float3), NULL, &OCL->err);
	set_ray_arr_ocl_set(sc);
	OCL->global = WIDTH * HEIGHT;
	OCL->err = clGetKernelWorkGroupInfo(OCL->ray_arr_kernel, OCL->device_id,
		CL_KERNEL_WORK_GROUP_SIZE, sizeof(OCL->local), &OCL->local, NULL);
	while (OCL->global % OCL->local != 0)
		OCL->local--;
	OCL->err = clEnqueueNDRangeKernel(OCL->commands, OCL->ray_arr_kernel,
					1, NULL, &OCL->global, &OCL->local, 0, NULL, NULL);
	clFinish(OCL->commands);
	OCL->err = clEnqueueReadBuffer(OCL->commands, *OCL->output,
	CL_TRUE, 0, sizeof(t_ray) * WIDTH * HEIGHT, RAY_ARR, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);
}

void	set_ray_arr_ocl_3(t_scene *sc)
{
	OCL->err = clSetKernelArg(OCL->ray_arr_kernel, 3,
							sizeof(cl_float3), &sc->cam.rot);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	set_ray_arr_ocl_2(sc);
}

void	set_ray_arr_ocl_2(t_scene *sc)
{
	OCL->err = clEnqueueWriteBuffer(OCL->commands, OCL->output[1], CL_TRUE,
						0, sizeof(cl_float3), &sc->cam.pos, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array (ray_arr)", 1);
	OCL->err = clEnqueueNDRangeKernel(OCL->commands, OCL->ray_arr_kernel,
				1, NULL, &OCL->global, &OCL->local,
				0, NULL, NULL);
	clFinish(OCL->commands);
	OCL->err = clEnqueueReadBuffer(OCL->commands, *OCL->output,
					CL_TRUE, 0, sizeof(t_ray) * WIDTH * HEIGHT,
					RAY_ARR, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);
}
