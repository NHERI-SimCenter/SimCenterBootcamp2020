#include <omp.h>
#include <stdio.h>
#include <time.h>

static int long numSteps = 1000000000;

int main() {

  // perform calculation
  double pi   = 0;
  double dx = 1./numSteps;
  double x = 0.5*x;
  double start = omp_get_wtime();
  
  // compute using Reduction

#pragma omp parallel for reduction(+:pi) private(x)
  for (int i=0; i<numSteps; i++) {
    x = (i+0.5)*dx;  
    pi += 4./(1.+x*x);
  }
  
  pi *= dx;
  
  printf("Reduction: PI = %16.8f in %.4g sec\n",pi,omp_get_wtime()-start);
  
  // compute using Synchronization    
  start = omp_get_wtime();  
#pragma omp parallel 
  {
    double sum = 0;
    double x = 0;
#pragma omp for
    for (int i=0; i<numSteps; i++) {
      x = (i+0.5)*dx;
      sum += 4./(1.+x*x);
    }
#pragma omp critical
    {
      pi += sum;
      // OTHER STUFF .. NOT TOO MUCH
    }
  }
  
  pi *= dx;
  
  printf("Synchronization: PI = %16.8f in %.4g sec\n",pi, omp_get_wtime()-start);

  // compute Serially
  start = omp_get_wtime();  
  {
    pi = 0;
    double sum = 0;
    double x  = dx*0.50;
    for (int i=0; i<numSteps; i++) {
     pi += 4./(1.+x*x);
      x += dx;
    }
    pi*=dx;
  }

  printf("Serially: PI = %16.8f in %.4g sec\n",pi, omp_get_wtime()-start);  

  // compute in parallel using dedicated loops
  start = omp_get_wtime();  
  int nThreads;
  double pSum[32][64]; // max num threads 32, cache line length >= 64doub;e
#pragma omp parallel 
  {
    int tid = omp_get_thread_num();
    int numT = omp_get_num_threads();
    if (tid == 0) nThreads = numT;

    pSum[tid][0] = 0;
    int start = tid * numSteps / numT;
    int end = (tid+1) * numSteps / numT;
    double xLocal = (start+0.5)*dx;

    if (tid == numT-1) 
      end = numSteps;
    for (int i=start; i < end; i++) {
     pSum[tid][0] += 4./(1.+xLocal*xLocal);
     xLocal += dx;
    }
  }  
  pi = 0;
  for (int i=0; i<nThreads; i++) {
    pi += pSum[i][0];
  }
  pi *= dx;

  printf("Parallel: PI = %16.8f in %.4g sec\n",pi, omp_get_wtime()-start);  
  return 0;
}
