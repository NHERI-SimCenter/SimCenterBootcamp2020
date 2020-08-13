#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DATA_SIZE 10000
#define PAD 16

int main(int argc, const char **argv) {
  int nThreads = 0;
  double dot = 0;

  double a[DATA_SIZE];
  for (int i=0; i<DATA_SIZE; i++) a[i] = i+1;

  double sum[64][PAD];
  for (int i=0; i<64; i++) sum[i][0] = 0;

  double tdata = omp_get_wtime();

#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int numT = omp_get_num_threads();
    if (tid == 0) 
      nThreads = numT;

    for (int i=tid; i<DATA_SIZE; i+= numT)
      sum[tid][0] += a[i]*a[i];
  }

  for (int i=0; i<nThreads; i++) 
    dot += sum[i][0];
  dot = sqrt(dot);

  tdata = omp_get_wtime() - tdata;
  printf("dot %f in time %f \n", dot, tdata);
  return 0;
}



