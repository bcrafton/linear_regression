#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H
#include "OpenCLCustom.h"
#include "linear_algebra.h"

float* gradient_descent(float* X, float* y, float* theta, float alpha, int m, int n, int itrs);
#endif