# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MEM_SIZE (1920000)
#define MAX_SOURCE_SIZE (0x100000)

int main()
{
	void *mlx = mlx_init();
	void *window = mlx_new_window(mlx, 800, 600, "OpenCL");
	int bits_per_pixel = 32;
	int line_size = 800 * 4;
	int endian = 0;
	void *image = mlx_new_image(mlx, 800, 600);
	// char *image_data = mlx_get_data_addr(image, &bits_per_pixel, &line_size, &endian);

	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem memobj = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;
	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;

	int *image_data = (int *)mlx_get_data_addr(image, &bits_per_pixel, &line_size, &endian);

	FILE *fp;
	char fileName[] = "./hello.cl";
	char *source_str;
	size_t source_size;
	
	/* Load the source code containing the kernel*/
	fp = fopen(fileName, "r");
	if (!fp) {
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
	
	/* Get Platform and Device Info */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	
	/* Create OpenCL context */
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	
	/* Create Command Queue */
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	
	/* Create Memory Buffer */
	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE,  MEM_SIZE * sizeof(char), NULL, &ret);
	
	/* Create Kernel Program from the source */
	program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	
	/* Build Kernel Program */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	
	if (ret == CL_BUILD_PROGRAM_FAILURE)
	{
		size_t log_size;
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		char *log = (char *) malloc(log_size);
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		printf("%s\n", log);
	}

	/* Create OpenCL Kernel */
	kernel = clCreateKernel(program, "hello", &ret);

	
	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
	
	/* Execute OpenCL Kernel */
	// ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, (size_t[3]){800, 600, 0}, NULL, 0, NULL, NULL);

 	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), image_data, 0, NULL, NULL);
	
	// printf("%0x\n", image_data[0]);
	// printf("%0x\n", image_data[1]);
	// printf("%0x\n", image_data[2]);
	
	/* Display Result */
	// puts(image_data);
	// mlx_image_data_put(mlx, window, 10, 10, 0xFFFFFF, image_data);
	mlx_put_image_to_window(mlx, window, image, 0, 0);
	
	/* Finalization */
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(memobj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	
	free(source_str);

	mlx_loop(mlx);
	
	return 0;
}
