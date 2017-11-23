#include <stdio.h>
#include "mpi.h"

int main (int argc, char** argv)
{
	int pid;
	int size;
	const int rootProcess = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
   	
	if (pid == rootProcess){
		char mensaje_send[4] = "hola";	
		MPI_Send(&mensaje_send, 4, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
	} else {
		char mensaje_recv[4];
		MPI_Recv(&mensaje_recv, 4, MPI_CHAR, rootProcess, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("mensaje: %s\nid de proceso: %d\nlongitud de mensaje: %d\n", mensaje_recv, pid, size);
	}
	MPI_Finalize();
	return 0;
}

