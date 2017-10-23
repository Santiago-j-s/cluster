#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank, size;
	MPI_Init(NULL, NULL); //inicializa MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //obtener id del proceso
	MPI_Comm_size(MPI_COMM_WORLD, &size); //numero de procesos

	printf("Hola mundo desde el proceso %d of %d \n", rank, size);
	MPI_Finalize(); //finaliza MPI
}
