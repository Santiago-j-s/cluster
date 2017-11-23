#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv)
{
int pid, npr;
int i, X;
int A[8], B[2], C[2];
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);
MPI_Comm_size(MPI_COMM_WORLD, &npr);
/* Inicializaciones en todos los procesos */
for(i=0; i<8; i++) A[i] = -1;
for(i=0; i<2; i++) B[i] = -1;
for(i=0; i<2; i++) C[i] = -1;
X = -1;
if (pid == 0)
{ for(i=0; i<8; i++) A[i] = i;
X = 6;
}
/* Broadcast de X desde P0 */
MPI_Bcast(&X, 1, MPI_INT, 0, MPI_COMM_WORLD);
printf("1: BC de P0 --> P%d y X = %d \n", pid, X);
MPI_Barrier(MPI_COMM_WORLD);
/* Reparto de A (8 elementos) desde P0 en trozos de tamaino 2, en B */
MPI_Scatter(&A[0], 2, MPI_INT, &B[0], 2, MPI_INT, 0, MPI_COMM_WORLD);
printf(" 2: SCATTER soy P%d y B = %d %d \n", pid, B[0], B[1]);
MPI_Barrier(MPI_COMM_WORLD);
/* Suma de los 4 vectores B (2 elementos) en el vector C en P0 */
MPI_Reduce(&B[0], &C[0], 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
printf(" 3: REDUCE en P%d C = %d %d \n", pid, C[0], C[1]);
MPI_Barrier(MPI_COMM_WORLD);
/* Suma de los 4 vectores B (2 elementos) en el vector C en todos los P */
MPI_Allreduce(&B[0], &C[0], 2, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
printf(" 4. ALLREDUCE en P%d C = %d %d \n", pid, C[0], C[1]);
MPI_Barrier(MPI_COMM_WORLD);
/* Recoleccion de los vectores B en el vector A en P0 */
for(i=0; i<2; i++) B[i] = B[i] + 10;
MPI_Gather(&B[0], 2, MPI_INT, &A[0], 2, MPI_INT, 0, MPI_COMM_WORLD);
printf(" 5: GATHER en P%d, A = %d %d %d %d %d %d %d %d\n", pid,
A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7]);
MPI_Barrier(MPI_COMM_WORLD);
/* Recoleccion de los vectores B en el vector A en todos los P */
MPI_Allgather(&B[0], 2, MPI_INT, &A[0], 2, MPI_INT, MPI_COMM_WORLD);
printf(" 6: ALLGATHER en P%d, A = %d %d %d %d %d %d %d %d\n", pid,
A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7]);
MPI_Finalize();
return 0;
} /* main */
