/*
* Benchmark dSFMT and ranlux performances.
*
* Dario Mapelli, mapelli.dario@gmail.com
*
* Simple analysis of the time required by the various operations.
* This benchmark tests only how quickly are the random numbers generated
* and uses huge arrays without saving them to the disk
* For each algorithm the test is performed 'test_num' times.
* Each test consist in generating 'rand_length' random numbers in [0,1]
* for 'repeat' times.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "ranlxd.h"
#include "dSFMT.h"
#include "dSFMT-api.h"
#include "ranlux-api.h"

int main (int numArg, char * listArg[])
{
	double max_ram_dimensions = 5. ; //GiB

	int rand_length = 1e5 ; // lenght of the random number array
	int repeat = 10 ; // during each test, the generator function is called `repeat` times
	int test_num = 2; // number of time that the test is repeated
	printf (" rand_length: %d\n", rand_length) ;
	printf (" repeat: %d\n", repeat ) ;
	printf (" test_num: %d\n", test_num ) ;

	//total generated nubmer by each algorithm
	long int rand_card = (long int) (rand_length*repeat*test_num) ;
	printf("rand_card: %e\n", (double) rand_card);
	//dimension of storage array
	double rand_arr_storage_dimension =
		(double) rand_card * sizeof(double) / 1024. / 1024. / 1024. ;
	printf("rand_arr_storage dimension: %f GiB \n", rand_arr_storage_dimension);

	if (rand_arr_storage_dimension > max_ram_dimensions) {
		printf("rand_arr_storage dimension too big\n");
		return 0;
	}

	//all the generated numbers are copied here, otherwise (if -O3 is chosen)
	//the compiler undestands that they are not saved anywhere nor printed and
	//the output_file binary doesnt contain the code to generate them
	double *rand_arr_storage;
	rand_arr_storage = (double*) malloc (sizeof(double)*rand_card) ;
	int i=0 ;
	for (i=0; i<rand_card; i++) {
		rand_arr_storage[i] = -1.;
	}

	//defined in time.h, used to compute the execution times
	clock_t start, end;
	double cpu_time_tot;
	//this is the array that will be used to generate the random numbers
	double *rand_arr;

	int counter=0;
	for (counter=0; counter<test_num; counter++) {
		printf("---------\ncounter: %d\n", counter);

		//-------RANLUX------------
		start = clock();
		int ranlux_check = ranlux_alloc (&rand_arr, rand_length) ;
		if (ranlux_check == 1 ){
			exit(EXIT_FAILURE) ;
		}
		rlxd_init(1,time(NULL)+counter);
		int i=0, j=0 ;
		for (i=0; i < repeat ; i++) {
			ranlxd(rand_arr, rand_length) ;
			for (j=0; j<rand_length; j++) {
				rand_arr_storage[i*rand_length+j] = rand_arr[j] ;
			}
		}
		free(rand_arr) ;
		end = clock();
		cpu_time_tot = ((double) (end - start)) / CLOCKS_PER_SEC ;
		printf("ranlux time: %f sec\n", cpu_time_tot);

		//-------dSFMT------------
		printf ("period of the dSFMT sequence multiple of 2^%d-1\n", DSFMT_MEXP);
		start = clock();
		int size = dsfmt_get_min_array_size();
		if (size <  rand_length) {
			size =  rand_length;
		}
		int dSFMT_check = dSFMT_alloc (&rand_arr, size) ;
		if (dSFMT_check == 1) {
			exit(EXIT_FAILURE) ;
		}
		dsfmt_gv_init_gen_rand( time (NULL)+counter ) ;
		for (i=0; i < repeat ; i++) {
			dsfmt_gv_fill_array_close_open(rand_arr, size);
			for (j=0; j<rand_length; j++) {
				rand_arr_storage[i*rand_length+j] = rand_arr[j] ;
			}
		}
		free(rand_arr) ;
		end = clock();
		cpu_time_tot = ((double) (end - start)) / CLOCKS_PER_SEC ;
		printf("dSFMT time: %f sec\n", cpu_time_tot);
	}


	free(rand_arr_storage) ;
	return 0;
}
