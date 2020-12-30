
// program to write n random values between 0 and maxVal to a file
// the values are written in one line

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  //
  // initialize random number generator
  //
  
  srand((unsigned int)time(0));  
  rand(); // i like to call it once, even with time

  //
  // create a vector of random numbers
  //

  int n = 5;
  float maxVal = 3;
  double theVector[n];
  for (int i=0; i<n; i++)
    theVector[i]= ((float)rand()/(float)RAND_MAX) * maxVal;

  //
  // write them to a file
  //
  
  FILE *filePtr = fopen("file2.out","a");

  for (int i=0; i<n; i++) {
    fprintf(filePtr,"%8.4f ",theVector[i]);
  }
  fprintf(filePtr,"\n");
  
  fclose(filePtr);
  
}
