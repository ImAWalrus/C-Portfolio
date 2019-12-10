#include <stdio.h>
#include <stdlib.h>
#define N 3
#define M 3

void allocate_mem_2d(float*** arr2d, int n, int m)
{
  *arr2d = (float**)malloc(n*sizeof(float*));
  for(int i=0; i<n; i++)
    (*arr2d)[i] = (float*)malloc(m*sizeof(float));
}

void allocate_mem_1d(float** arr1d, int m)
{
  *arr1d = (float*)malloc(m*sizeof(float));
}

void matrix_vector_mult(float* h_x, float* h_b, float** h_A, int n, int m)
{
  int i,j;
  float sum_b = 0.0;
  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      sum_b = sum_b + h_A[i][j]*h_x[j];
      }
    h_b[i] = sum_b;
    printf("%f\n",h_b[i]);
    sum_b = 0.0;
    }
}
int main()
{
  float** h_A;
  float* h_x,*h_b;
  int i,j;
  float sum_b = 0.0;

  allocate_mem_2d(&h_A,N,M);
  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      h_A[i][j] = j;
      //printf("h_a:%f\n",h_A[i][j]);
    }
  }
  allocate_mem_1d(&h_x,M);
  allocate_mem_1d(&h_b,M);
  for(j=0;j<M;j++)
  {
    h_x[j] = j;
    h_b[j] = 0.0;
    //printf("h_x:%f h_b%f\n", h_x[j], h_b[j]);
  }

  matrix_vector_mult(h_x, h_b, h_A, N, M);

  free(h_x);
  free(h_b);
  for(i =0;i<N;i++){
    free(h_A[i]);
  }
  free(h_A);

  return 0;
}
