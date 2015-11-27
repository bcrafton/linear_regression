#include "../header/OpenCLCustom.h"

OpenCLConfig* getOpenCLConfig()
{
	OpenCLConfig* config = (OpenCLConfig*)malloc(sizeof(OpenCLConfig));

	cl_platform_id* platforms = NULL;
    cl_uint num_platforms;
	cl_device_id* devices = NULL;   
    cl_uint num_devices;

	clGetPlatformIDs(0, NULL, &num_platforms);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * num_platforms);
	clGetPlatformIDs(num_platforms, platforms, NULL);

	// only using first platform and first device for now.
	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_DEFAULT, 0, NULL, &num_devices);
	devices = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);
	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_DEFAULT, num_devices, devices, NULL);

	cl_int ret;
	cl_context context = clCreateContext(NULL, 1, &devices[0], NULL, NULL, &ret);
	cl_command_queue command_queue = clCreateCommandQueue(context, devices[0], 0, &ret);

	config->platforms = platforms;
	config->num_platforms = num_platforms;
	config->devices = devices;
	config->num_devices = num_devices;
	config->context = context;
	config->command_queue = command_queue;

	return config;
}

float* loadMatrix(const int height, const int width, FILE *fp)
{
	// create the matrix ... still going to be single dimensional.
	float* matrix = new float[width*height];
	// input file into the matrix.
	for (int i = 0; i < width*height; ++i) {
		fscanf(fp, "%f", &matrix[i]);
	}
	return matrix;
}

program_src* load_program_string(char* source_file)
{
	FILE *fp;
    char *source_str;
    size_t source_size;
 
    fp = fopen(source_file, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }

    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);

	program_src* ret = (program_src*)malloc(sizeof(program_src));
	ret->size = source_size;
	ret->src = source_str;

    fclose( fp );

	return ret;
}