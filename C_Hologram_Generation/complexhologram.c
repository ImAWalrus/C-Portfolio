#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 600
#define M 600


int main()
{
  int i,j;
  double *ipx; // 1 Row by 600 columns
  double *ipy; // 1 Row by 600 columns
  double *film; // 600 Rows by 600 columns

  double object_points[][3] = {{1,0,4},{1,2,4},{-1,0,4},{-1,2,4},{1,0,6},{1,2,6},{-1,0,6},{-1,2,6}};

  double wavelength = 0.000000630; //Wavelength of red laser light
  double sampling = 0.0254/600; //1 inch in meter divided by 600

  int dim = 1; //Dimensions
  double range = dim*0.0254/2;


  /* Allocate Mem For 2D Array */
  ipx=malloc(M*sizeof(double));
  ipy=malloc(M*sizeof(double));

  /* Loop through 1-600 Vector */
  /* CHECK FUNCTION */
  double back_range = -1*range; // Start at the end of range
  for(i = 0; i < 600; i++){ //Start at Negavtive end of range
      ipx[i] = back_range;
      ipy[i] = back_range;
      back_range += sampling;

  }
  /* Fill Film with 0 VALUES*/
  film=malloc(N*M*sizeof(double));
  for(i = 0; i < N; i++){
    for(j = 0; j < M; j++){
        film[(i*M)+j] = 0.0;
        //printf("%f",film[i]);
    }
  }

  double dx; //Distance x
  double dy; //Distance y
  double dz; //Distance z

  double complexwave;
  double distance;

  int point_size = 8;
  int ipi_size = 600;
  FILE *fp;//Range?

  double e = 0;
  for(int o = 0; o < point_size; o++){
    for(int i = 0; i < ipi_size; i++){
      for(int j = 0; j< ipi_size; j++){
         //Flatten Array
         /* DX, DY, DZ stay constant */
          dx = object_points[o][0] - ipx[i];
          dy = object_points[o][1] - ipy[j];
          dz = object_points[o][2] - 0;
          distance = sqrt(dx*dx + dy*dy + dz*dz);
          e = cos((2*3.14/wavelength)*distance);
          film[(i*M)+j] = film[(i*M)+j] + e;

      }
    }

  }
  free(ipx);
  free(ipy);

  fp = fopen("test3.csv","w");
  for(int i = 0; i < N; i++){
    for(int j = 0; j< M; j++){
      fprintf(fp,"%f,",film[(i*M)+j]);
    }
    fprintf(fp,"\n");
  }
  free(film);
  return 0;
}
