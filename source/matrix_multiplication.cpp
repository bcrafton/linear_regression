#include "../header/linear_algebra.h"

void matrix_multiplication(OpenCLConfig* config, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B, cl_mem &a_mem_obj,
					 cl_mem& b_mem_obj, cl_mem& c_mem_obj)
{
	cl_int ret;
	program_src* src = load_program_string("source\\open_cl\\matrix_multiplication.cl");
	int matrix_a_size = ROWS_A * COLS_A;
	int matrix_b_size = COLS_A * COLS_B;
	int matrix_c_size = ROWS_A * COLS_B;

	cl_program program = clCreateProgramWithSource(config->context, 1, (const char **)&(src->src), (const size_t *)&(src->size), &ret);

	clBuildProgram(program, 1, &config->devices[0], NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "matrix_multiplication", &ret);

	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
	clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&ROWS_A);
	clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&COLS_A);
	clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&ROWS_B);
	clSetKernelArg(kernel, 6, sizeof(cl_mem), (void *)&COLS_B);

	size_t global_item_size[] = {ROWS_A, COLS_B};
	// leaving this as 1 for now because figure it out later.
	// so good stack overflow thread can help figure these out.
	// prob easier to manually enter.
	size_t local_item_size[] = {1, 1};
	// 2 is for 2d.
    clEnqueueNDRangeKernel(config->command_queue, kernel, 2, NULL, global_item_size, local_item_size, 0, NULL, NULL);
}