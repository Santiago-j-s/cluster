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
		char mensaje_send[4] ="hola";
		int i;
		for(i = 0; i < size; i++){
			if(i!= pid){
			MPI_Send(&mensaje_send, cntProcess, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
			MPI_Send(&mensaje_send, cntProcess, MPI_CHAR, 2, 0, MPI_COMM_WORLD);		
			}
		}
	} else {
		char mensaje_recv[cntProcess];
		MPI_Recv(&mensaje_recv, cntProcess, MPI_CHAR, rootProcess, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("caracter:\t%s, process id:\t%d, size:\t%d \n", mensaje_recv, pid, size);
	}
	MPI_Finalize();
	return 0;
}
