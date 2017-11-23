#include <mpi.h>
#include <stdio.h>
//#include <stdlib.h>

int main(int argc, char** argv) {
	int nro_proceso;
	int valor = 5;
	int procesos;

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &nro_proceso);
	MPI_Comm_size(MPI_COMM_WORLD, &procesos);
	
	if (nro_proceso != 0) {
		MPI_Recv(
			&valor,
			 1,
			 MPI_INT,
			 nro_proceso - 1,
			 0,
		         MPI_COMM_WORLD,
			 MPI_STATUS_IGNORE
		);

		printf(
			"Proceso %d recibe valor %d desde el proceso %d\n",
		   	nro_proceso,
		       	valor,
			nro_proceso - 1
		);
	} 

	//envia mientras no sea el utlimo proceso
	if (nro_proceso < procesos-1) {
		MPI_Send(
			&valor, 
			 1,
			 MPI_INT, 
			 (nro_proceso + 1),
			 0, 
			 MPI_COMM_WORLD
		);

		printf(
			"Proceso %d envia valor %d al proceso %d\n",
			nro_proceso,
		       	valor,
			nro_proceso + 1
		);
	}

	MPI_Finalize();
}

