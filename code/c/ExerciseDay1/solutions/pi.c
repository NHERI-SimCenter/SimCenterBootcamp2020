#include <stdio.h>
#include <time.h>

static int long numSteps = 1000000000;

int main() {

  // perform calculation
  double pi   = 0;
  double dx = 1./numSteps;
  double x  = dx*0.50;
  
  for (int i=0; i<numSteps; i++) {
    pi += 4./(1.+x*x);
    x += dx;
  }
  
  pi *= dx;
  
  printf("PI = %16.14f\n",pi);
  return 0;
}
