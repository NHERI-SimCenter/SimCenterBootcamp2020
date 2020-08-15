#include <stdio.h>
#include "omp.h"

int main(int argc, char **argv) {

    int num_steps = 1000000000;
    int i;

    double x=0;
    double sum = 0.0;
    double step = 1.0/(double) num_steps;

#pragma omp parallel private(i,x) 
   {
      int ID=omp_get_thread_num();
      printf("starting thread %d\n",ID);

#pragma omp for reduction(+:sum) schedule(static)
      for (i=0; i<num_steps; i++){
         x=(i+0.5)*step;
         sum += 4.0/(1.0+x*x);
      }
   }
   
   double pi=step*sum;

   printf("pi = %20.16f\n",pi);

   return 0;
}
