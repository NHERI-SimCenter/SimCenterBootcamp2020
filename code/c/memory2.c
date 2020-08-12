#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int n;
  double **matrix1 =0;

  printf("enter n: ");
  scanf("%d", &n);
  
  // allocate memory & set the data
  matrix1 = (double **)malloc(n*sizeof(double *));
  for (int i=0; i<n; i++) {
    matrix1[i] = (double *)malloc(n*sizeof(double));
    for (int j=0; j<n; j++)
      matrix1[i][j] = i;
  }
  
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++)
      printf("(%d,%d) %.4f\n", i,j, matrix1[i][j]);
  }

  // free the data
  for (int i=0; i<n; i++)
    free(matrix1[i]);
  free(matrix1);

}
