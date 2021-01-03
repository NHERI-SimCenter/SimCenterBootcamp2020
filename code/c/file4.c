
// program to read n floats from two input files & compare!
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
  float *theVector = (float *)malloc(n*sizeof(float));
  for (int i=0; i<n; i++)
    theVector[i]= ((float)rand()/(float)RAND_MAX) * maxVal;

  //
  // read vectors stored in 2 files
  //
  
  FILE *fileBinaryPtr = fopen("file3.out","rb");
  FILE *fileAsciiPtr = fopen("file3Ascii.out","r");  

  float *theVectorB = (float *)malloc(n*sizeof(float));
  float *theVectorA = (float *)malloc(n*sizeof(float));  
  
  // write data in 1 call
  fread(theVectorB, sizeof(float), n, fileBinaryPtr);  

  for (int i=0; i<n; i++) {
    fscanf(fileAsciiPtr,"%f ",&theVectorA[i]);
  }

  for (int i=0; i<n; i++) {
    float errBinary = theVectorB[i]-theVector[i];
    float errAscii =  theVectorA[i]-theVector[i];
    printf("%.7e %.7e \n", errBinary, errAscii);
  }
  printf("\n");
  
  fclose(fileBinaryPtr);
  fclose(fileAsciiPtr);}
  
