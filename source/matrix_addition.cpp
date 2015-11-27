#include "../header/linear_algebra.h"

void matrix_addition(OpenCLConfig* config, int ROWS, int COLS, cl_mem &a_mem_obj, cl_mem& b_mem_obj, cl_mem& c_mem_obj)
{
	cl_int ret;
	program_src* src = load_program_string("source\\open_cl\\matrix_addition.cl");
	int matrix_size = ROWS * COLS;

	cl_program program = clCreateProgramWithSource(config->context, 1, (const char **)&(src->src), (const size_t *)&(src->size), &ret);

	clBuildProgram(program, 1, &config->devices[0], NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "matrix_addition", &ret);

	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
	clSetKernelArg(kernel, 3, sizeof(int), (void *)&ROWS);
	clSetKernelArg(kernel, 4, sizeof(int), (void *)&COLS);

	size_t global_item_size[] = {ROWS, COLS};
	// leaving this as 1 for now because figure it out later.
	size_t local_item_size[] = {1, 1};
	// 2 is for 2d.
	clEnqueueNDRangeKernel(config->command_queue, kernel, 2, NULL, global_item_size, local_item_size, 0, NULL, NULL);
}