#ifndef RANLUX_H
#define RANLUX_H

#ifndef RANLUX_C
int ranlux_alloc (double** array, int dimension) ;
int ranlux_alloc_verbose (double** array, int dimension) ;
int ranlux_alloc_fill (double** array, int dimension, int seed) ;
int ranlux_alloc_fill_verbose (double** array, int dimension, int seed) ;
#endif


#endif
