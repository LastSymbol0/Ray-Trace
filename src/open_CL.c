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

void	build_cl_source(t_scene *sc, char *KernelSource)
{
	// Create the compute program from the source buffer
	OCL->program = clCreateProgramWithSource(OCL->context, 1,
	(const char **) &KernelSource, NULL, &OCL->err);
	if (!OCL->program)
	  ft_err("Failed to create compute program", 1);

	// Build the program executable
	OCL->err = clBuildProgram(OCL->program, 0, NULL, NULL, NULL, NULL);
	if (OCL->err != CL_SUCCESS) {
	  size_t len;
	  char buffer[12048];

	  ft_putendl("Failed to build program executable");
	  clGetProgramBuildInfo(OCL->program, OCL->device_id, CL_PROGRAM_BUILD_LOG,
				  sizeof(buffer), buffer, &len);
	  ft_err(buffer, 1);
	  exit(1);
	}

	// Create the compute kernel in the program
	OCL->kernel = clCreateKernel(OCL->program, "set_ray_arr", &OCL->err);
	if (!OCL->kernel || OCL->err != CL_SUCCESS)
		ft_err("Failed to create compute kernel", 1);
}

void	test_openCL(t_scene *sc)
{
	char	*KernelSource;
	cl_mem	output;
	t_vec	*results;

	results = (t_vec *)ft_memalloc(sizeof(t_vec) * WIDTH * HEIGHT);

	clock_t end, start;
	start = clock();
	OCL = init_ocl();
	KernelSource = read_file("src/set_ray_arr.cl", 5508);
	printf("\nKernelSource:\n%s\n", KernelSource);
	build_cl_source(sc, KernelSource);
	output = clCreateBuffer(OCL->context, CL_MEM_WRITE_ONLY,
			sizeof(t_vec) * WIDTH * HEIGHT, NULL, &OCL->err);
	if (!output || OCL->err != CL_SUCCES) 
		ft_err("Failed to allocate device memory", 1);

	OCL->err  = clSetKernelArg(OCL->kernel, 0, sizeof(int), &HEIGHT);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err  = clSetKernelArg(OCL->kernel, 1, sizeof(int), &WIDTH);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err  = clSetKernelArg(OCL->kernel, 2, sizeof(t_vec), &sc->cam.rot);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);
	OCL->err  = clSetKernelArg(OCL->kernel, 3, sizeof(cl_mem), &output);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);

	OCL->global = HEIGHT * WIDTH;
	OCL->local = 100;

	OCL->err = clEnqueueNDRangeKernel(OCL->commands, OCL->kernel,
			       1, NULL, &OCL->global, &OCL->local,
			       0, NULL, NULL);


	clFinish(OCL->commands);
	// Read back the results from the device to verify the output
	OCL->err = clEnqueueReadBuffer(OCL->commands, output,
				    CL_TRUE, 0, sizeof(t_vec) * WIDTH * HEIGHT,
				    results, 0, NULL, NULL );
	end = clock();
	printf("GPU: The above code block was executed in %.4f second(s)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);

	// int i = -1;
	// while(++i < WIDTH * HEIGHT){
	// 	printf("%f %f %f;\t", results[i].x, results[i].y, results[i].z);
	// 	if (i % HEIGHT == 0)
	// 		ft_putendl("");
	// }
	


}