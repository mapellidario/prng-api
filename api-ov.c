/*
Test of dSFMT and ranlux.

Simplest possible program

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
	int rand_length = 10 ;

	//all the generated numbers are copied here, otherwise (if -O3 is chosen)
	//the compiler undestands that they are not saved anywhere nor printed and
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

    //this is the array that will be used to generate the random numbers
	double *rand_arr;

    // ranlux
    // alloc_ranlux (&rand_arr, rand_length) ;
    // ranlxd(rand_arr, rand_length) ;
	int ranlux_check = ranlux_alloc_fill(&rand_arr, rand_length, time(NULL)) ;
	if (ranlux_check == 1) {
		exit(EXIT_FAILURE) ;
	}
    for (i=0; i<rand_length; i++) {
        ranlux_storage[i] = rand_arr[i] ;
    }
	free(rand_arr) ;

    // dSFMT
    printf("\n");
    int size = dsfmt_get_min_array_size();
    if (size <  rand_length) {
        size =  rand_length;
    } //dSFMT ha una dimensione minima per poter lavorare
    // dSFMT_alloc (&rand_arr, size) ;
    // dsfmt_gv_init_gen_rand( time (NULL) ) ;
    // dsfmt_gv_fill_array_close_open(rand_arr, size);
	int dSFMT_check = dSFMT_alloc_fill(&rand_arr, size, time(NULL));
	if (dSFMT_check == 1) {
		exit(EXIT_FAILURE) ;
	}
    for (i=0; i<rand_length; i++) {
        dsfmt_storage[i] = rand_arr[i] ;
    }
    free(rand_arr) ;

	printf("\n");
	printf("ranlux\n");
    for (i=0; i<rand_length; i++) {
        printf("%f\n", ranlux_storage[i]) ;
    }
	printf("\n");
	printf("dsfmt\n");
	for (i=0; i<rand_length; i++) {
		printf("%f\n", dsfmt_storage[i]) ;
    }

	//Fine Programma
	free(ranlux_storage) ;
	free(dsfmt_storage) ;

	return 0;
}
