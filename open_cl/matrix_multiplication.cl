__kernel void matrix_multiplication(__global const float *A, __global const float *B, __global float *C, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	int j = get_global_id(1);
    // Do the operation
	int tmp = 0;
	
	// i hope this is right, may need to test out for sure because
	// this is not great test .
	for(int k = 0; k < COLS_A; k++)
	{
		tmp += A[j*COLS_A + k] * B[k*ROWS_B + i];
	}
	C[j*COLS_A + i] = tmp;
}