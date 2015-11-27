#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H
#include "OpenCLCustom.h"

void matrix_multiplication(OpenCLConfig* config, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B, cl_mem &a_mem_obj,
					 cl_mem& b_mem_obj, cl_mem& c_mem_obj);

void matrix_subtraction(OpenCLConfig* config, int ROWS, int COLS, cl_mem &a_mem_obj, cl_mem& b_mem_obj, cl_mem& c_mem_obj);

void matrix_transpose(OpenCLConfig* config, int ROWS, int COLS, cl_mem &source_buf1, cl_mem& dst_buf);

void scalar_multiplication(OpenCLConfig* config, float scalar, int ROWS, int COLS, cl_mem &a_mem_obj, cl_mem& c_mem_obj);

void matrix_addition(OpenCLConfig* config, int ROWS, int COLS, cl_mem &a_mem_obj, cl_mem& b_mem_obj, cl_mem& c_mem_obj);

#endif