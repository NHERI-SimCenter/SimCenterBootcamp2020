#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* ******************** *
 * set default values   *
 * ******************** */
#define N  851558400


int main(int argc, char **argv) {

    // initialize an internal timer
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    // set up thread number from defaults and potential user input

    int n=N;

    if (argc >=2) {
	n = atoi(argv[1]);
	if (n < 100) n = 100;
    }

    double pi=0.0;

    double dx = 1./n;
    double x = 0.5*dx;

    for (int i=0; i<n; i++) {
        x = (0.5 + i)*dx;
	pi += 4./(1.+x*x);
    }

    pi *= dx ;

    // check end time

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // nice printing the result

    printf("pi = %20.16f (%10.6f secs)\n", pi, cpu_time_used);

    return 0;
}

