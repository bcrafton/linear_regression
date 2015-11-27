__kernel void scalar_multiplication(__global const float *A, float scalar, __global float *C, int ROWS, int COLS)
{
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	int j = get_global_id(1);
    // Do the operation
	C[i*COLS + j] = A[i*COLS + j] * scalar;
}