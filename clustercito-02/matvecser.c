#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
int N, i, j;
double sum=0.0;
double *Am, **A, *B, *C, *D;
printf("\n Longitud de los vectores (<1000) = ");
scanf("%d" , &N);
/* reserva de memoria */
Am = (double *) malloc (N*N * sizeof(double));
A = (double **) malloc (N * sizeof(double *)); // para usar dos dimensiones
for(i=0; i<N; i++) A[i] = &Am[i*N];
B = (double *) malloc (N * sizeof(double));
C = (double *) malloc (N * sizeof(double));
D = (double *) malloc (N * sizeof(double));
/* inicializar variables */
for(i=0; i<N; i++)
{
for(j=0; j<N; j++) A[i][j] = (double) (N-i)*0.1/N;
B[i] = (double) i*0.05/N;
}
/* comienzo del calculo */
for (i=0; i<N; i++)
{
C[i] = 0.0;
for (j=0; j<N; j++) C[i] = C[i] + Am[i*N+j] * B[j]; // o A[i][j]
}
sum = 0.0;
for (i=0; i<N; i++)
{
D[i] = 0.0;
for (j=0; j<N; j++) D[i] = D[i] + Am[i*N+j] * C[j];
sum = sum + D[i]*C[i];
}
/* resultados */
printf("\n\n sum = %1.3f \n", sum);
printf(" D[0] = %1.3f, D[N/2] = %1.3f, D[N-1)] = %1.3f\n\n", D[0],D[N/2],D[N-1]);
return 0;
}
