#include <stdio.h>
#include <mpi.h>

int main (int argc, char** argv)
{
	int pid;
	int size;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
   	

	char mensaje_send[4] = "hola";
	MPI_Bcast(&mensaje_send, 4, MPI_CHAR, 0, MPI_COMM_WORLD);

	printf("mensaje:\t%s, proceso:\t%d, longitud:\t%d \n", mensaje_send, pid, size);

	MPI_Finalize();
	return 0;
}

