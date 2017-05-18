/*
Test of dSFMT and ranlux.

In depth time analysis.

*/

//C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//personali
#include "ranlxd.h" //ranlux include file
#include "dSFMT.h" //dSFMT include file
#include "dSFMT-api.h"
#include "ranlux-api.h"

int main (int numArg, char * listArg[])
{
	printf( "Simple dSFMT and ranlux usage\n\n" ) ;

    // parameters setting
	int rand_length = 1e8 ;
	double max_ram_dimensions = 8. ; //GiB
	printf (" rand_length: %d\n", rand_length) ;
	double rand_arr_dimension =
		(double) rand_length * sizeof(double) / 1024. / 1024. / 1024. ;
	printf(" rand_arr dimension: %f GiB \n\n", rand_arr_dimension);
	if (2*rand_arr_dimension > max_ram_dimensions) {
		printf("rand_arr too big (check on ram)\n");
		return 0;
	}

	//all the generated numbers are copied here, otherwise (if -O3 is chosen)
	//the compiler may undestand that they are not saved anywhere nor printed and
	//the output_file binary doesnt contain the code to generate them
	double *ranlux_storage = (double*) malloc (sizeof(double)*rand_length) ;
    int i=0;
	for (i=0; i<rand_length; i++) {
		ranlux_storage[i] = -1.;
	}

	double *dsfmt_storage = (double*) malloc (sizeof(double)*rand_length) ;
	for (i=0; i<rand_length; i++) {
		dsfmt_storage[i] = -1.;
	}

	//defined in time.h, used to compute the execution times
	clock_t start, checkpoint, checkpoint1, checkpoint2, end;
	double alloc_time, gen_time, copy_time, free_time, cpu_time_tot;

    //this is the array that will be used to generate the random numbers
	double *rand_arr;

    // ranlux
	start = clock();
	int ranlux_check = ranlux_alloc (&rand_arr, rand_length) ;
	if (ranlux_check==1){
		exit(EXIT_FAILURE) ;
	}
    checkpoint = clock();
	rlxd_init(1,time(NULL));
	ranlxd (rand_arr,rand_length);
    checkpoint1 = clock();
    for (i=0; i<rand_length; i++) {
        ranlux_storage[i] = rand_arr[i] ;
    }
    checkpoint2 = clock();
    free(rand_arr) ;
    end = clock();
    alloc_time = ((double) (checkpoint - start)) / CLOCKS_PER_SEC ;
    printf("ranlux alloc time: %10f sec\n", alloc_time);
    gen_time = ((double) (checkpoint1 - checkpoint)) / CLOCKS_PER_SEC ;
    printf("ranlux gen time:   %10f sec\n", gen_time);
    copy_time = ((double) (checkpoint2 - checkpoint1)) / CLOCKS_PER_SEC ;
    printf("ranlux copy time:  %10f sec\n", copy_time);
    free_time = ((double) (end - checkpoint2)) / CLOCKS_PER_SEC ;
    printf("ranlux free time:  %10f sec\n", free_time);
    cpu_time_tot = ((double) (end - start)) / CLOCKS_PER_SEC ;
    printf("ranlux total time: %10f sec\n", cpu_time_tot);

    // dSFMT
    printf("\n");
    start = clock();
    int size = dsfmt_get_min_array_size();
    if (size <  rand_length) {
        size =  rand_length;
    } //dSFMT ha una dimensione minima per poter lavorare
    int dSFMT_check = dSFMT_alloc (&rand_arr, size) ;
	if (dSFMT_check == 1) {
		exit(EXIT_FAILURE) ;
	}
    checkpoint = clock();
    dsfmt_gv_init_gen_rand( time (NULL) ) ;
    dsfmt_gv_fill_array_close_open(rand_arr, size);
    checkpoint1 = clock();
    for (i=0; i<rand_length; i++) {
        dsfmt_storage[i] = rand_arr[i] ;
    }
    checkpoint2 = clock();
    free(rand_arr) ;
    end = clock();
    alloc_time = ((double) (checkpoint - start)) / CLOCKS_PER_SEC ;
    printf("dSFMT alloc time: %10f sec\n", alloc_time);
    gen_time = ((double) (checkpoint1 - checkpoint)) / CLOCKS_PER_SEC ;
    printf("dSFMT gen time:   %10f sec\n", gen_time);
    copy_time = ((double) (checkpoint2 - checkpoint1)) / CLOCKS_PER_SEC ;
    printf("dSFMT copy time:  %10f sec\n", copy_time);
    free_time = ((double) (end - checkpoint2)) / CLOCKS_PER_SEC ;
    printf("dSFMT free time:  %10f sec\n", free_time);
    cpu_time_tot = ((double) (end - start)) / CLOCKS_PER_SEC ;
    printf("dSFMT total time: %10f sec\n", cpu_time_tot);

    for (i=0; i<rand_length; i++) {
        // printf("%f\n", ranlux_storage[i]) ;
    }
	for (i=0; i<rand_length; i++) {
        // printf("%f\n", dsfmt_storage[i]) ;
    }

	// End
	free(ranlux_storage) ;
	free(dsfmt_storage) ;

	return 0;
}
