/*
Example of usage of dSFMT and ranlux.

Memory allocation separated from random number generation

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
	int repeat = 3 ;

	// the output is saved in a file
	char filename[64];
	int idx_file = (int) time(NULL);
	printf ("File produced ID: %d\n", idx_file);
	sprintf (filename, "rand_%d.txt", idx_file);
	FILE *output_file = fopen (filename, "w+");

    //this is the array that will be used to generate the random numbers
	double *rand_arr;

    // ranlux
	printf("\nranlux\n");
	fprintf(output_file, "ranlux\n\n") ;
	int ranlux_check = ranlux_alloc(&rand_arr, rand_length) ;
	if (ranlux_check == 1) {
		exit(EXIT_FAILURE) ;
	}
	rlxd_init(1,time(NULL));
	int i=0, j=0;
	for (j=0; j<repeat; j++){
		ranlxd(rand_arr, rand_length) ;
		for (i=0; i<rand_length; i++) {
	        fprintf(output_file, "%.15f\n", rand_arr[i]) ;
	    }
		fprintf(output_file, "\n") ;
	}
	fprintf(output_file, "\n") ;
	free(rand_arr) ;

    // dSFMT
    printf("\ndSFMT\n");
	fprintf(output_file, "dSFMT\n\n") ;
    int size = dsfmt_get_min_array_size();
    if (size <  rand_length) {
        size =  rand_length;
    } //dSFMT ha una dimensione minima per poter lavorare
    int dSFMT_check = dSFMT_alloc (&rand_arr, size) ;
	if (dSFMT_check == 1) {
		exit(EXIT_FAILURE) ;
	}
    dsfmt_gv_init_gen_rand( time (NULL) ) ;
	for (j=0; j<repeat; j++){
	    dsfmt_gv_fill_array_close_open(rand_arr, size);
	    for (i=0; i<rand_length; i++) {
	        fprintf(output_file, "%.15f\n", rand_arr[i]) ;
	    }
		fprintf(output_file, "\n") ;
	}
    free(rand_arr) ;

	//Fine Programma
	fclose(output_file) ;

	return 0;
}
