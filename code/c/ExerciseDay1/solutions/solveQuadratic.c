// program to solve quadratic equation
//        ax^2 + bx + c = 0
//
// soln: x = -b/2a +/- sqrt(b^2-4ac)/2a
//
// write a program to take 3 inputs and output the soln
// deal with possible errors in input, i.e. b^2-4ac negative

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {

  if (argc != 4) {
    printf("Usage: appName a b c\n");
    exit(-1);
  }

  float a = atof(argv[1]);
  float b = atof(argv[2]);
  float c = atof(argv[3]);

  float b2minus4ac = b*b-4*a*c;

  if (b2minus4ac > 0.0) {
    
    double bDiv2a = b/(2*a);
    double other = sqrt(b2minus4ac)/(2*a);
    double x1 = bDiv2a - other;
    double x2 = bDiv2a + other;    
    printf("Double Solution x1:  %f  x2: %f\n", x1, x2);    

  } else if (b2minus4ac == 0.0) {

    double x = -b/(2*a);
    printf("Single Solution is %f\n", x);
    
  } else {
    
    double bDiv2a = b/(2*a);
    double other = sqrt(-b2minus4ac)/(2*a);
    double x1 = bDiv2a - other;
    double x2 = bDiv2a + other;
    
    printf("Complex Solution x1:  %f + %fi, x2: %f + %fi\n", bDiv2a, other, bDiv2a, -other);    
    
  }

  
  return 0;
}

