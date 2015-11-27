__kernel void matrix_addition(__global const float *A, __global const float *B, __global float *C, int ROWS, int COLS)
{
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	int j = get_global_id(1);
    // Do the operation
	C[i*COLS + j] = A[i*COLS + j] + B[i*COLS + j];
}