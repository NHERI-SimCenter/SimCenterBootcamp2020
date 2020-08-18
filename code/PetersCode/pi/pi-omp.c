#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "omp.h"

/* ******************** *
 * set default values   *
 * ******************** */
#define N  1000000000
#define NUM_THREADS 8

#define CHATTY 1
// #define CHATTY 0


int main(int argc, char **argv) {

    // initialize an internal timer
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    // set up thread number from defaults and potential user input

    int num_threads = NUM_THREADS;

    if (argc >=2) {
	num_threads = atoi(argv[1]);
    }
    if (num_threads < 1) num_threads = 1;
    if (num_threads > 8) num_threads = 8;

    // configure parallel arrays and workflow

    //omp_set_dynamic(0);
    omp_set_num_threads(num_threads);

    double dx = 1./(double) N;

    double pi=0.0;

// #pragma omp parallel private(i,x,s)
#pragma omp parallel
{
    int ID=omp_get_thread_num();

    if (CHATTY) printf("starting thread %d ...\n",ID);

    double s = 0.;

    for (int i=ID; i<N; i+=num_threads) {
        double x = (0.5 + i)*dx;
	s += 4./(1.+x*x);
    }
    if (CHATTY) printf("... (%d): %20.16f\n",ID,s*dx*num_threads);

#pragma omp atomic
    pi += s;
}

    pi *= dx ;

    // check end time

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // nice printing the result

    printf("pi = %20.16f (%10.6f secs)\n", pi, cpu_time_used);

    return 0;
}

