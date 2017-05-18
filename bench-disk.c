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
	int rand_length = 1e6 ;

	double max_disk = 100. ; //MiB
	double disk_dimension =
		(double) 18 * 2 * rand_length / 1024. / 1024. ;
	printf(" rand_arr storage dimension: %f MiB \n\n", disk_dimension);
	if (2*disk_dimension > max_disk) {
		printf("rand_arr too big (check on disk)\n");
		return 0;
	}

	char filename[64];
	int idx_file = (int) time(NULL);
	printf ("File produced ID: %d\n", idx_file);
	sprintf (filename, "rand_%d.txt", idx_file);
	FILE *output_file = fopen (filename, "w+");

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
	int i=0;
    for (i=0; i<rand_length; i++) {
		fprintf(output_file, "%.15f\n", rand_arr[i]);
    }
    checkpoint2 = clock();
    free(rand_arr) ;
    end = clock();
    alloc_time = ((double) (checkpoint - start)) / CLOCKS_PER_SEC ;
    printf("ranlux alloc time:    %10f sec\n", alloc_time);
    gen_time = ((double) (checkpoint1 - checkpoint)) / CLOCKS_PER_SEC ;
    printf("ranlux gen time:      %10f sec\n", gen_time);
    copy_time = ((double) (checkpoint2 - checkpoint1)) / CLOCKS_PER_SEC ;
    printf("ranlux fprintf time:  %10f sec\n", copy_time);
    free_time = ((double) (end - checkpoint2)) / CLOCKS_PER_SEC ;
    printf("ranlux free time:     %10f sec\n", free_time);
    cpu_time_tot = ((double) (end - start)) / CLOCKS_PER_SEC ;
    printf("ranlux total time:    %10f sec\n", cpu_time_tot);

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
		fprintf(output_file, "%.15f\n", rand_arr[i]);
    }
    checkpoint2 = clock();
    free(rand_arr) ;
    end = clock();
    alloc_time = ((double) (checkpoint - start)) / CLOCKS_PER_SEC ;
    printf("dSFMT alloc time:    %10f sec\n", alloc_time);
    gen_time = ((double) (checkpoint1 - checkpoint)) / CLOCKS_PER_SEC ;
    printf("dSFMT gen time:      %10f sec\n", gen_time);
    copy_time = ((double) (checkpoint2 - checkpoint1)) / CLOCKS_PER_SEC ;
    printf("dSFMT fprintf time:  %10f sec\n", copy_time);
    free_time = ((double) (end - checkpoint2)) / CLOCKS_PER_SEC ;
    printf("dSFMT free time:     %10f sec\n", free_time);
    cpu_time_tot = ((double) (end - start)) / CLOCKS_PER_SEC ;
    printf("dSFMT total time:    %10f sec\n", cpu_time_tot);

	//Fine Programma
	fclose(output_file);

	return 0;
}
