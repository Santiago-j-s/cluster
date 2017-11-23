#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank, size , nodo_len;
	char nodo[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(NULL, NULL); //inicializa MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //obtener id del proceso
	MPI_Comm_size(MPI_COMM_WORLD, &size); //numero de procesos
	MPI_Get_processor_name(nodo, &nodo_len); //nombre del nodo
	printf("Hola Mundo desde el proceso %d de %d en el nodo %s\n", rank, size, nodo);
	MPI_Finalize(); //finaliza MPI
}

