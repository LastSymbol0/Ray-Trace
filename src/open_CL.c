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

void	set_cl_params(t_scene *sc)
{
	// t_ray* results = RAY_ARR; // results returned from device
	// unsigned int correct;               // number of correct results returned
	cl_mem input1;                       // device memory used for the input array
	cl_mem input2;                       // device memory used for the input array
	cl_mem input3;                       // device memory used for the input array
	cl_mem output;                      // device memory used for the output array


	// Create the device memory vectors
	input1 = clCreateBuffer(OCL->context,  CL_MEM_READ_ONLY,
			sizeof(int), NULL, NULL);
	input2 = clCreateBuffer(OCL->context,  CL_MEM_READ_ONLY,
			sizeof(int), NULL, NULL);
	input3 = clCreateBuffer(OCL->context,  CL_MEM_READ_ONLY,
			sizeof(t_vec), NULL, NULL);
	output = clCreateBuffer(OCL->context, CL_MEM_WRITE_ONLY,
			sizeof(t_ray) * sc->width * sc->height , NULL, NULL);
	OCL->output = output;
	if (!input1) 
		ft_err("Failed to allocate device memory", 1);

	// Transfer the input vector into device memory
	OCL->err = clEnqueueWriteBuffer(OCL->commands, input1,
			     CL_TRUE, 0, sizeof(int),
			    &sc->width, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array", 1);

	OCL->err = clEnqueueWriteBuffer(OCL->commands, input2,
			     CL_TRUE, 0, sizeof(int),
			    &sc->height, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array", 1);

	OCL->err = clEnqueueWriteBuffer(OCL->commands, input3,
			    CL_TRUE, 0, sizeof(t_vec),
			    &sc->cam.rot, 0, NULL, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to write to source array", 1);
	
	// Set the arguments to the compute kernel
	OCL->err  = clSetKernelArg(OCL->kernel, 0, sizeof(cl_mem), &input1);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);

			OCL->err  = clSetKernelArg(OCL->kernel, 1, sizeof(cl_mem), &input2);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);

			OCL->err  = clSetKernelArg(OCL->kernel, 2, sizeof(cl_mem), &input3);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);

			OCL->err  = clSetKernelArg(OCL->kernel, 3, sizeof(cl_mem), &output);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to set kernel arguments", 1);

	// Get the maximum work group size for executing the kernel on the device
	OCL->err = clGetKernelWorkGroupInfo(OCL->kernel, OCL->device_id,
				 CL_KERNEL_WORK_GROUP_SIZE,
				 sizeof(OCL->local), &OCL->local, NULL);
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to retrieve kernel work group info", 1);
}

void	test_openCL(t_scene *sc)
{
	char *KernelSource;

	OCL = init_ocl();
	KernelSource = read_file("src/set_ray_arr.cl", 5508);
	printf("\nKernelSource:\n%s\n", KernelSource);
	build_cl_source(sc, KernelSource);
	set_cl_params(sc);
	
	OCL->err = clEnqueueNDRangeKernel(OCL->commands, OCL->kernel,
			       1, NULL, &OCL->global, &OCL->local,
			       0, NULL, NULL);
	clFinish(OCL->commands);


		  // Read back the results from the device to verify the output
	//
	OCL->err = clEnqueueReadBuffer(OCL->commands, OCL->output,
				    CL_TRUE, 0, sizeof(t_ray) * sc->width * sc->height,
				    RAY_ARR, 0, NULL, NULL );
	if (OCL->err != CL_SUCCESS)
		ft_err("Failed to read output array", 1);
}