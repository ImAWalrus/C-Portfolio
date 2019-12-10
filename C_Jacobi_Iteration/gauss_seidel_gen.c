#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 4

    //----------Read File Function----------//
void readFile(FILE** ptr, const char filename[50], const char mode[10]){
   *ptr = fopen(filename,mode);
   if(filename == NULL){
     printf("Error reading file");
   }
}

  //----------Allocation Function----------//
void allocate_mem_2d(float*** arr2d, int n, int m)
{
  *arr2d = (float**)malloc(n*sizeof(float*));
  for(int i=0; i<n; i++)
    (*arr2d)[i] = (float*)malloc(m*sizeof(float));
}

int main(){
  //----------Variable Declaration----------//
  float** A_mtrx;
  float** B_vector;
  float** C_vector;

  float** x_initial;
  float x_old[N][1] = {{0},{0},{0},{0}};
  float** x_new;
  float** error_x;
  float temp_vec;

  float error_max = 999;
  float epsilon = 0.001;
  float sum_x = 0.0;
  float sum_error = 0.0;
  int count = 0;

  //----------Memory Allocation----------//
  allocate_mem_2d(&A_mtrx,N,N);
  allocate_mem_2d(&B_vector,N,1);
  allocate_mem_2d(&C_vector,N,N);
  allocate_mem_2d(&x_initial,N,1);
  allocate_mem_2d(&x_new,N,1);
  allocate_mem_2d(&error_x,N,1);

  //----------Get Data From Files----------//
  FILE *A_ptr,*B_ptr;
  readFile(&A_ptr,"A_vector.dat","r");
  readFile(&B_ptr,"B_vector.dat","r");

  //----------Variable Initilization----------//
  for(int i = 0;i<N;i++){
    for(int j =0;j<N;j++){
        fscanf(A_ptr, "%f",&temp_vec);
        A_mtrx[i][j] = temp_vec;
    }
  }

  for(int i =0;i<N;i++){
    fscanf(B_ptr, "%f",&temp_vec);
    B_vector[i][0] = temp_vec;
  }

  for(int i =0;i<N;i++){
    for(int j =0;j<N;j++){
      C_vector[i][j] = 0;
      x_initial[i][0] = x_old[i][0];
      error_x[i][0] = 999;
    }
  }

  //----------Print A | B----------//
  for(int i =0;i<N;i++){
    for(int j = 0; j<N;j++){
    printf("%0.2f ", A_mtrx[i][j]);
    }
  printf("\n");
  }
  printf("\n");

  for(int i =0;i<N;i++){
    printf("%0.2f\n",B_vector[i][0]);
  }
  printf("\n");



  //----------Calculations----------//
  while(error_max > epsilon){
    for(int i = 0; i < N; i++){
      sum_x = 0.0;
      for(int j = 0; j < N; j++){
        if(i != j){
          C_vector[i][j] = A_mtrx[i][j]*x_old[j][0];
          sum_x = sum_x + C_vector[i][j];
        }
      }
      x_new[i][0] = (B_vector[i][0] - sum_x) / A_mtrx[i][i];
    }
    sum_error = 0.0;

  for(int k = 0; k<N; k++){
    error_x[k][0] = x_new[k][0] - x_old[k][0];
    sum_error = sum_error + error_x[k][0] * error_x[k][0];
  }
  error_max = sqrt(sum_error);
  printf("Count: %d | Errror: %0.2f\n",count,error_max);
  count = count + 1;

  for(int l = 0;l < N; l++){
    x_old[l][0] = x_new[l][0];
    }
  }

  for(int i =0;i<N;i++){
    printf("%0.2f\n",x_new[i][0]);
}

  //----------Free Memory----------//
  free(A_mtrx);
  for(int i =0;i<N;i++){
      free(A_mtrx[i]);
    }

  free(B_vector);
  free(C_vector);
  free(x_initial);
  free(error_x);

  return 0;
}
