#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main(int argc, char **argv) {

    int num_steps = 1000000000;

    double pi = 0.0;
    double step = 1./num_steps;

    if (argc>1) omp_set_num_threads(atoi(argv[1]));

#pragma omp parallel for reduction(+:pi)
    for (int i=0; i<num_steps; i++) {
	double x=(i+0.5)*step;
	pi += 4.0/(1.0+x*x);
    }
   
    pi *= step;

    printf("pi = %20.16f\n",pi);

    return 0;
}
