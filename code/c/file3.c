
// program to write n random values between 0 and maxVal out
// output is sent to 2 files:
//   1. file.out a binary file
//   2. fileAscii.out an ascii file (i.e. readable by human)

// written: fmk

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  //
  // note: initializing with same seed
  //
  
  srand(100);
  //srand((unsigned int)time(0)); // the usual way to call srand
  rand(); // i like to call it once

  //
  // create a vector of random numbers
  //

  int n = 10;
  float maxVal = 3;
  float theVector[n];
  for (int i=0; i<n; i++)
    theVector[i]= ((float)rand()/(float)RAND_MAX) * maxVal;

  //
  // write them to a file
  //
  
  FILE *fileBinaryPtr = fopen("file3.out","wb");
  FILE *fileAsciiPtr = fopen("file3Ascii.out","w");  

  // write data in 1 call
  fwrite(theVector, sizeof(float), n, fileBinaryPtr);  

  for (int i=0; i<n; i++) {
    fprintf(fileAsciiPtr,"%f ",theVector[i]);
  }
  fprintf(fileAsciiPtr,"\n");
  
  fclose(fileBinaryPtr);
  fclose(fileAsciiPtr);  
  
}
