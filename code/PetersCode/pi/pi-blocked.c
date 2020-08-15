#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* ******************** *
 * set default values   *
 * ******************** */
//#define N  851558400
#define N  (2*4*6*8)
#define NUM_THREADS 8

//#define CHATTY 1
#define CHATTY 0


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
    //if (num_threads > 8) num_threads = 8;

    int n=N/num_threads;

    double dx = 1./(double)n/(double)num_threads;

    double *sum = (double *)malloc(num_threads*sizeof(double));

    for ( int ID=0; ID<num_threads;ID++) {

	if (CHATTY) printf("starting thread %d\n",ID);

	double s = 0.;

	double x = (double)ID / num_threads;
	x += 0.5*dx;

	for (int i=0; i<n; i++,x+=dx) {
	    s += 4./(1.+x*x);
	}
	
	if (CHATTY) printf("... (%d): %20.16f\n",ID,s);

	sum[ID] = s;
    }

    double pi=0.0;
    for ( int ID=0; ID<num_threads;ID++) {
    	pi += sum[ID];
    }
    pi *= dx ;

    free(sum); sum=0;

    // check end time

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // nice printing the result

    printf("pi = %20.16f (%10.6f secs)\n", pi, cpu_time_used);

    return 0;
}

