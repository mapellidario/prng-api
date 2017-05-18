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
#define DSFMTAPI_C

#include<stdlib.h>
#include<stdio.h>
#include "dSFMT.h" //dSFMT include file



//Memory allocation

int dSFMT_alloc (double** array, int size)  {

#if defined(__APPLE__) || \
	(defined(__FreeBSD__) && __FreeBSD__ >= 3 && __FreeBSD__ <= 6)
//	printf("malloc used\n");
	*array = malloc(sizeof(double) * size);
	if (*array == NULL) {
		printf("can't allocate memory.\n");
		return 1;
	}
	return 0;

#elif defined(_POSIX_C_SOURCE)
//	printf("posix_memalign used\n");
	if ( posix_memalign((void **)&(*array), 16, sizeof(double) * size) != 0) {
		printf("can't allocate memory.\n");
		return 1;
	}
	return 0;

#elif defined(__GNUC__) && (__GNUC__ > 3 || \
		(__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
//	printf("memalign used\n");
	*array = memalign(16, sizeof(double) * size);
	if (*array == NULL) {
		printf("can't allocate memory.\n");
		return 1;
	}
	return 0;

#else // in this case, gcc doesn't suppport SSE2
	*array = malloc(sizeof(double) * size);
	if (*array == NULL) {
//		printf("can't allocate memory.\n");
		return 1;
	}
	return 0;

#endif

}

int dSFMT_alloc_verbose (double** array, int size)  {
	//Alloco la memoria allineandola propriamente, cosicchè dSFMT lavori a dovere

	printf("size of random dSMFT array: %ld byte = ", sizeof(double) * size) ;
	printf("%f GiB\n", sizeof(double) * size / 1024. / 1024. / 1024.) ;

#if defined(__APPLE__) || \
	(defined(__FreeBSD__) && __FreeBSD__ >= 3 && __FreeBSD__ <= 6)
//	printf("malloc used\n");
	*array = malloc(sizeof(double) * size);
	if (*array == NULL) {
		printf("can't allocate memory.\n");
		return 1;
	}
	return 0;

#elif defined(_POSIX_C_SOURCE)
//	printf("posix_memalign used\n");
	if ( posix_memalign((void **)&(*array), 16, sizeof(double) * size) != 0) {
		printf("can't allocate memory.\n");
		return 1;
	}
	return 0;

#elif defined(__GNUC__) && (__GNUC__ > 3 || \
		(__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
//	printf("memalign used\n");
	*array = memalign(16, sizeof(double) * size);
	if (*array == NULL) {
		printf("can't allocate memory.\n");
		return 1;
	}
	return 0;

#else // in this case, gcc doesn't suppport SSE2
	*array = malloc(sizeof(double) * size);
	if (*array == NULL) {
//		printf("can't allocate memory.\n");
		return 1;
	}
	return 0;

#endif
}


int dSFMT_alloc_fill (double** array, int dimension, int seed)  {
	dsfmt_t dsfmt;
	int dSFMT_check = dSFMT_alloc(array, dimension) ;
	if (dSFMT_check == 1){
		return 1;
	}
	dsfmt_init_gen_rand(&dsfmt, seed);
	dsfmt_fill_array_close_open(&dsfmt, *array, dimension);
	return 0;
}

int dSFMT_alloc_fill_verbose (double** array, int dimension, int seed)  {
	dsfmt_t dsfmt;
	int dSFMT_check = dSFMT_alloc_verbose (array, dimension) ;
	if (dSFMT_check == 1){
		return 1;
	}
	dsfmt_init_gen_rand(&dsfmt, seed);
	dsfmt_fill_array_close_open(&dsfmt, *array, dimension);
	return 0;
}
