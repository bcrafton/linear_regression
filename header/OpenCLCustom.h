#ifndef OPENCLCUSTOM_H
#define OPENCLCUSTOM_H
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <malloc.h>
using namespace std;
 
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
 
#define MAX_SOURCE_SIZE (0x100000)

typedef struct OpenCLConfig{
	cl_platform_id* platforms;
	cl_uint num_platforms;
	cl_device_id* devices;
	cl_uint num_devices;
	cl_context context;
	cl_command_queue command_queue;
} OpenCLConfig;

typedef struct program_src
{
	char* src;
	size_t size;
} program_src;

OpenCLConfig* getOpenCLConfig();
float* loadMatrix(const int height, const int width, FILE *fp);
program_src* load_program_string(char* source_file);

#endif