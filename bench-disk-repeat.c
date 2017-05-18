/*
* Benchmark dSFMT and ranlux performances.
*
* Dario Mapelli, mapelli.dario@gmail.com
*
* Simple time analysis of the time required bythe algorithms.
* For each algorithm the test is performed 'test_num' times.
* Each test consist in generating 'rand_length' random numbers in [0,1]
* for 'repeat' times.
* The output is saved in ./install/rand_%d.txt
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
	double max_file_dimensions = 100. ; //MiB

	int rand_length = 1e5 ; // lenght of the random number array
	int repeat = 10 ; // during each test, the generator function is called `repeat` times
	int test_num = 2; // number of time that the test is repeated
	printf (" rand_length: %d\n", rand_length) ;
	printf (" repeat: %d\n", repeat ) ;
	printf (" test_num: %d\n", test_num ) ;

	//total generated nubmer by each algorithm
	long int rand_card = (long int) (rand_length*repeat*test_num) ;
	printf("rand_card: %e\n", (double) rand_card);
	//approximate dimension of output_file file
	double file_dimension = (double) rand_card * 20. / 1024. / 1024. ;
	printf("file_dimension : %f MiB \n", file_dimension);
	if (file_dimension > max_file_dimensions) {
		printf("file dimension too big\n");
		return 0;
	}

	int idx_file = (int) time(NULL);
	printf ("File produced ID: %d\n", idx_file);
	char filename[64];
	sprintf (filename, "rand_%d.txt", idx_file);
	FILE *output_file = fopen (filename, "w+");

	//defined in time.h, used to compute the execution times
	clock_t start, checkpoint, checkpoint1, checkpoint2, end;
	double alloc_time, gen_time, copy_time, free_time, cpu_time_tot;

	//this is the array that will be used to generate the random numbers
	double *rand_arr;

	int counter=0;
	for (counter=0; counter<test_num; counter++) {
		printf("---------\ncounter: %d\n", counter);

		//-------RANLUX------------
		fprintf(output_file, "Ranlux\n");
		start = clock();
		int ranlux_check = ranlux_alloc (&rand_arr, rand_length) ;
		if (ranlux_check == 1 ){
			exit(EXIT_FAILURE) ;
		}
		rlxd_init(1,time(NULL)+counter);
		int i=0, j=0 ;
		for (i=0; i < repeat ; i++) {
			ranlxd(rand_arr, rand_length) ;
			fprintf(output_file, "\n");
			for (j=0; j<rand_length; j++) {
				fprintf(output_file, "%2.15f\n", rand_arr[j]);
			}
		}
		free(rand_arr) ;
		end = clock();
		cpu_time_tot = ((double) (end - start)) / CLOCKS_PER_SEC ;
		printf("ranlux time: %f sec\n", cpu_time_tot);

		//-------dSFMT------------
		printf ("period of the dSFMT sequence multiple of 2^%d-1\n", DSFMT_MEXP);
		fprintf(output_file, "\ndSFMT\n");
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
			fprintf(output_file, "\n");
			for (j=0; j<rand_length; j++) {
				fprintf(output_file, "%2.15f\n", rand_arr[j]);
			}
		}
		free(rand_arr) ;
		end = clock();
		cpu_time_tot = ((double) (end - start)) / CLOCKS_PER_SEC ;
		printf("dSFMT time: %f sec\n", cpu_time_tot);
	}

	fclose(output_file);
	return 0;
}
