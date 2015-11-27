#include "../header/linear_regression.h"
#include "../header/linear_algebra.h"

void gradient_descent(OpenCLConfig* config, float* X, float* y, float* theta, float alpha, int m, int n, int itrs)
{
	// can directly create buffers in clcreatebuffer
	// want to move away from writing buffer in the lin alg files ... no need to do it there.
	cl_int ret;
	cl_mem X_buf = clCreateBuffer(config->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, m*n * sizeof(float), X, &ret);
    cl_mem y_buf = clCreateBuffer(config->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, m * sizeof(float), y, &ret);
    cl_mem theta_buf = clCreateBuffer(config->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, n * sizeof(float), theta, &ret);	
	//
	cl_mem h_buf = clCreateBuffer(config->context, CL_MEM_READ_WRITE, m * sizeof(float), NULL, &ret);
    cl_mem errors_buf = clCreateBuffer(config->context, CL_MEM_READ_WRITE, m * sizeof(float), NULL, &ret);
    cl_mem tmp_buf = clCreateBuffer(config->context, CL_MEM_READ_WRITE, n * sizeof(float), NULL, &ret);
	cl_mem XT_buf = clCreateBuffer(config->context, CL_MEM_READ_WRITE, n*m * sizeof(float), NULL, &ret);
    cl_mem gradient_buf = clCreateBuffer(config->context, CL_MEM_READ_WRITE, n * sizeof(float), NULL, &ret);
	
	matrix_transpose(config, m, n, X_buf, XT_buf);
	for(int i = 0; i < 5; i++)
	{
		cout << "iteration# " << i << endl;
		matrix_multiplication(config, m, n, n, 1, X_buf, theta_buf, h_buf);
		matrix_subtraction(config, m, 1, h_buf, y_buf, errors_buf);
		matrix_multiplication(config, n, m, m, 1, XT_buf, errors_buf, tmp_buf);
		scalar_multiplication(config, alpha/m, n, 1, tmp_buf, gradient_buf);
		matrix_subtraction(config, n, 1, theta_buf, gradient_buf, theta_buf);
	}

	 clEnqueueReadBuffer(config->command_queue, theta_buf, CL_TRUE, 0, n*1 * sizeof(float), theta, 0, NULL, NULL);
	 for(int i = 0; i < n; i++)
	 {
		 cout << theta[i] << ", ";
	 }
}

int main(void) 
{
	// will want to make better use of this idea, make more dynamic so it runs on all platforms and devices.
	// wud also be good to start doing the error checks everyone else seems to do.
	OpenCLConfig* config = getOpenCLConfig();

	int m = 47;
	int n = 2;
	float alpha = .01;
	float* X = loadMatrix(m, n, fopen("X.csv", "r"));
	float* y = loadMatrix(m, 1, fopen("Y.csv", "r"));
	float* theta = (float*)malloc(sizeof(float) * n);
	theta[0] = 0;
	theta[1] = 0;

	gradient_descent(config, X, y, theta, alpha, m, n, 100);

	getchar();
}