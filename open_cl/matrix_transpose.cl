__kernel void matrix_transpose(__global const float *A, __global float *C, int ROWS, int COLS)
{
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	int j = get_global_id(1);
    // Do the operation
	C[j*ROWS + i] = A[i*COLS + j];
}