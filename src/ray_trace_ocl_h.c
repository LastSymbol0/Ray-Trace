/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace_ocl_h.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:32:40 by aillia            #+#    #+#             */
/*   Updated: 2019/09/29 14:32:42 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	ray_trace_ocl_alloc(t_scene *sc)
{
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
	LIGHT_BUFF = clCreateBuffer(OCL[1].context, CL_MEM_READ_ONLY,
						sizeof(t_light) * sc->light_count, NULL, &OCL[1].err);
	if (!LIGHT_BUFF || OCL[1].err != CL_SUCCES)
		ft_err("Failed to allocate device memory4", 1);
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, OBJECTS_BUFF, CL_TRUE, 0,
			sizeof(t_obj) * (sc->obj_count), sc->objects, 0, NULL, NULL);
}

void	ray_trace_ocl_set(t_scene *sc)
{
	OCL[1].err = clSetKernelArg(OCL_OIK, 0, sizeof(cl_mem), &RAY_ARR_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments1", 1);
	OCL[1].err = clSetKernelArg(OCL_OIK, 1, sizeof(cl_mem), &OBJECTS_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err = clSetKernelArg(OCL_OIK, 3, sizeof(int), &sc->obj_count);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err = clSetKernelArg(OCL_OIK, 4, sizeof(cl_mem), &PIXELS_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err = clSetKernelArg(OCL_OIK, 2, sizeof(cl_mem), &LIGHT_BUFF);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err = clSetKernelArg(OCL_OIK, 5, sizeof(int), &sc->light_count);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err = clSetKernelArg(OCL_OIK, 6, sizeof(float), &sc->ambient);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
	OCL[1].err = clSetKernelArg(OCL_OIK, 7, sizeof(float),
													&sc->max_reflections);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments2", 1);
}

void	ray_trace_ocl_set_work_size(t_scene *sc)
{
	OCL[1].global = WIDTH * HEIGHT;
	OCL[1].err = clGetKernelWorkGroupInfo(OCL_OIK, OCL[1].device_id,
				CL_KERNEL_WORK_GROUP_SIZE,
				sizeof(OCL[1].local), &OCL[1].local, NULL);
	while (OCL[1].global % OCL[1].local != 0)
		OCL[1].local--;
}

void	ray_trace_ocl(t_scene *sc)
{
	object_intersect_build_ocl_source(sc,
		read_file("src/object_intersect.cl", 65534), "ray_cast");
	ray_trace_ocl_alloc(sc);
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, RAY_ARR_BUFF, CL_TRUE, 0,
			sizeof(t_ray) * WIDTH * HEIGHT, RAY_ARR, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (ray_arr)", 1);
	OCL[1].err = clEnqueueWriteBuffer(OCL[1].commands, LIGHT_BUFF, CL_TRUE, 0,
			sizeof(t_light) * sc->light_count, sc->lights, 0, NULL, NULL);
	if (OCL[1].err != CL_SUCCESS)
		ft_err("Failed to write to source array (lights)", 1);
	ray_trace_ocl_set(sc);
	ray_trace_ocl_set_work_size(sc);
	OCL[1].err = clEnqueueNDRangeKernel(OCL[1].commands, OCL_OIK,
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
