/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_CL.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:50:57 by aillia            #+#    #+#             */
/*   Updated: 2019/08/15 16:50:58 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_OpenCL	*init_ocl(void)
{
	t_OpenCL *ocl;

	// Connect to a compute device
	ocl = (t_OpenCL *)ft_memalloc(sizeof(t_OpenCL));
	if ((ocl->err = clGetPlatformIDs(1, &ocl->Platform, NULL)) != CL_SUCCES)
		ft_err("Failed to find a platform", 1);

	// Get a device of the appropriate type
	ocl->err = clGetDeviceIDs(ocl->Platform, CL_DEVICE_TYPE_GPU, 1, &ocl->device_id, NULL);
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

	return(ocl);
}

void	object_intersect_build_ocl_source(t_scene *sc, char *KernelSource, char *KernelName)
{
	// Create the compute program from the source buffer
	OCL->object_intersect_program = clCreateProgramWithSource(OCL->context, 1,
	(const char **) &KernelSource, NULL, &OCL->err);
	if (!OCL->object_intersect_program)
	  ft_err("Failed to create compute program", 1);

	// Build the program executable
	OCL->err = clBuildProgram(OCL->object_intersect_program, 0, NULL, NULL, NULL, NULL);
	if (OCL->err != CL_SUCCESS) {
	  size_t len;
	  char buffer[120048];

	  ft_putendl("Failed to build program executable");
	  clGetProgramBuildInfo(OCL->object_intersect_program, OCL->device_id, CL_PROGRAM_BUILD_LOG,
				  sizeof(buffer), buffer, &len);
	  ft_err(buffer, 1);
	  exit(1);
	}

	// Create the compute kernel in the program
	OCL->object_intersect_kernel = clCreateKernel(OCL->object_intersect_program, KernelName, &OCL->err);
	if (!OCL->object_intersect_kernel || OCL->err != CL_SUCCESS)
		ft_err("Failed to create compute kernel", 1);
}

void	ray_arr_build_ocl_source(t_scene *sc, char *KernelSource, char *KernelName)
{
	// Create the compute program from the source buffer
	OCL->ray_arr_program = clCreateProgramWithSource(OCL->context, 1,
	(const char **) &KernelSource, NULL, &OCL->err);
	if (!OCL->ray_arr_program)
	  ft_err("Failed to create compute program", 1);

	// Build the program executable
	OCL->err = clBuildProgram(OCL->ray_arr_program, 0, NULL, NULL, NULL, NULL);
	if (OCL->err != CL_SUCCESS) {
	  size_t len;
	  char buffer[12048];

	  ft_putendl("Failed to build program executable");
	  clGetProgramBuildInfo(OCL->ray_arr_program, OCL->device_id, CL_PROGRAM_BUILD_LOG,
				  sizeof(buffer), buffer, &len);
	  ft_err(buffer, 1);
	  exit(1);
	}

	// Create the compute kernel in the program
	OCL->ray_arr_kernel = clCreateKernel(OCL->ray_arr_program, KernelName, &OCL->err);
	if (!OCL->ray_arr_kernel || OCL->err != CL_SUCCESS)
		ft_err("Failed to create compute kernel", 1);
}

void	set_ray_arr_ocl(t_scene *sc)
{
	char	*KernelSource;
	cl_mem	output;
	
	KernelSource = read_file("src/set_ray_arr.cl", 5508);
	printf("\nKernelSource:\n%s\n", KernelSource);
	ray_arr_build_ocl_source(sc, KernelSource, "set_ray_arr");
	output = clCreateBuffer(OCL->context, CL_MEM_WRITE_ONLY,
			sizeof(t_ray) * WIDTH * HEIGHT, NULL, &OCL->err);
	if (!output || OCL->err != CL_SUCCES) 
		ft_err("Failed to allocate device memory", 1);

	OCL->err  = clSetKernelArg(OCL->ray_arr_kernel, 0, sizeof(int), &HEIGHT);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err  = clSetKernelArg(OCL->ray_arr_kernel, 1, sizeof(int), &WIDTH);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err  = clSetKernelArg(OCL->ray_arr_kernel, 2, sizeof(t_vec), &sc->cam.pos);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err  = clSetKernelArg(OCL->ray_arr_kernel, 3, sizeof(t_vec), &sc->cam.rot);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err  = clSetKernelArg(OCL->ray_arr_kernel, 4, sizeof(cl_mem), &output);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);

	OCL->global = HEIGHT * WIDTH;
	OCL->local = 1;

	OCL->err = clEnqueueNDRangeKernel(OCL->commands, OCL->ray_arr_kernel,
			       1, NULL, &OCL->global, &OCL->local,
			       0, NULL, NULL);


	clFinish(OCL->commands);
	// Read back the results from the device to verify the output
	OCL->err = clEnqueueReadBuffer(OCL->commands, output,
				    CL_TRUE, 0, sizeof(t_ray) * WIDTH * HEIGHT,
				    RAY_ARR, 0, NULL, NULL );
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);

	// int i = -1;
	// while(++i < WIDTH * HEIGHT){
	// 	printf("%f %f %f;\t", results[i].x, results[i].y, results[i].z);
	// 	if (i % HEIGHT == 0)
	// 		ft_putendl("");
	// }
	


}