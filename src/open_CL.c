/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_CL.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:50:57 by aillia            #+#    #+#             */
/*   Updated: 2019/09/03 15:34:10 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_OpenCL	*init_ocl(void)
{
	t_OpenCL *ocl;

	// Connect to a compute device
	ocl = (t_OpenCL *)ft_memalloc(sizeof(t_OpenCL) * 2);
	if ((ocl->err = clGetPlatformIDs(1, &ocl->Platform, NULL)) != CL_SUCCES)
		ft_err("Failed to find a platform", 1);

	// Get a device of the appropriate type
	ocl->err = clGetDeviceIDs(ocl->Platform, USED_CL_DEVICE, 1, &ocl->device_id, NULL);
	if (ocl->err != CL_SUCCESS)
		ft_err("Failed to create a device group", 1);

	// Create a compute context
	ocl->context = clCreateContext(0, 1, &ocl->device_id, NULL, NULL, &ocl->err);
	if (!ocl->context)
		ft_err("Failed to create a compute context", 1);

	// Create a command commands
	ocl->commands = clCreateCommandQueue(ocl->context, ocl->device_id, 0, &ocl->err);
	if (!ocl->commands)
		ft_err("Failed to create a command commands", 1);
	ocl++;
	if ((ocl->err = clGetPlatformIDs(1, &ocl->Platform, NULL)) != CL_SUCCES)
		ft_err("Failed to find a platform", 1);

	// Get a device of the appropriate type
	ocl->err = clGetDeviceIDs(ocl->Platform, USED_CL_DEVICE, 1, &ocl->device_id, NULL);
	if (ocl->err != CL_SUCCESS)
		ft_err("Failed to create a device group", 1);

	// Create a compute context
	ocl->context = clCreateContext(0, 1, &ocl->device_id, NULL, NULL, &ocl->err);
	if (!ocl->context)
		ft_err("Failed to create a compute context", 1);

	// Create a command commands
	ocl->commands = clCreateCommandQueue(ocl->context, ocl->device_id, 0, &ocl->err);
	if (!ocl->commands)
		ft_err("Failed to create a command commands", 1);
	ocl--;
	return(ocl);
}

