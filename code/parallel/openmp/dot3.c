#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DATA_SIZE 10000

int main(int argc, const char **argv) {
  double dot = 0;
  double a[DATA_SIZE];
  for (int i=0; i<DATA_SIZE; i++) {
    a[i] = i+1;
  }

  double tdata = omp_get_wtime();

#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int numT = omp_get_num_threads();
    double sum = 0.;

#pragma omp for
    for (int i=tid; i<DATA_SIZE; i+= numT)
      sum += a[i]*a[i];

#pragma omp_critical
    dot += sum;
  }
  
  dot = sqrt(dot);
  tdata = omp_get_wtime() - tdata;
  printf("dot %f in time %f \n", dot, tdata);
  return 0;
}



