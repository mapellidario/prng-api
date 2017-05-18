/*******************************************************************************
* Here are defined the functions that allocate memory for and fill up the arrays
* containing the random numbers.
* ranlux and dSFMT work better if they create all the random numbers all
* in once, so it is preferable to generate and store as much as random numbers
* as possible in huge arrays
*
* NOTE: to use the malloc indside a function is necesary to pass the pointer
* to the array. this means that double pointars are passed to these functions
*******************************************************************************/
#define RANLUX_C

#include<stdlib.h>
#include<stdio.h>
#include "ranlxd.h" //ranlux include file

//Memory allocation
int ranlux_alloc (double** array, int dimension) {
	*array = NULL ;
	long int size_array = sizeof(double) * (dimension) ;

	*array = (double *) malloc ( size_array );
	if (*array == NULL){
		free (*array);
		printf ("ranlux: memory allocation failed\n") ;
		return 1;
	}
	return 0;
}

int ranlux_alloc_verbose (double** array, int dimension) {
	*array = NULL ;
	long int size_array = sizeof(double) * (dimension) ;
	printf("size of random ranlux array: %ld byte = ", size_array) ;
	printf("%f GiB\n", (double)size_array / 1024. / 1024. / 1024.) ;

	*array = (double *) malloc ( size_array );
	if (*array == NULL){
		free (*array);
		printf ("ranlux: memory allocation failed\n") ;
		return 1;
	}
	return 0;
}

int ranlux_alloc_fill (double** array, int dimension, int seed) {

	int check_allocation = ranlux_alloc (array, dimension) ;
	if (check_allocation == 1)  {
		return 1;
	}
	rlxd_init(1,seed) ;
	ranlxd (*array, dimension) ;
	return 0;
}

int ranlux_alloc_fill_verbose (double** array, int dimension, int seed) {
	int check_allocation = ranlux_alloc_verbose (array, dimension) ;
	if (check_allocation == 1)  {
		return 1;
	}
	rlxd_init(1,seed) ;
	ranlxd (*array, dimension) ;
	return 0;
}
