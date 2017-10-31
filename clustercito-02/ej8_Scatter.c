#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
int main(int argc, char **argv)
{
int long_vec, i;
int *vector;
int *result;
int *vector_recv;
int sum;
int size, pid;

MPI_Init(&argc, &argv);

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);

long_vec = 4;

MPI_Barrier(MPI_COMM_WORLD);
// Procesamiento del vector
if (pid == 0) {
	sum=0;
	printf("\nNumero de procesos: %d\n", size);
	printf("\nLongitud del vector: %d\n", long_vec);

	//scanf("%d", &long_vec); // Multiplo del numero de procesos
	result = (int*)malloc(sizeof(int)*long_vec);
	vector = (int*)malloc(sizeof(int)*long_vec);	

	if(long_vec % size != 0) {
		printf("Longitud del vector tiene que ser multiplo de: %d\n", size);
		return 1;
	}
	
	for(i=0; i < long_vec; i++) 
		vector[i] = rand() % 100 - 50; // inicializacion del vector
			

	for(i=0; i < long_vec; i++) //Muestra lo que hay antes
		printf("posicion %d tiene %d\n", i,vector[i]); 
	
	for (i=0; i < long_vec; i++)  // Calcula la suma de todos los elementos
		sum = sum + vector[i];					
	
}

MPI_Barrier(MPI_COMM_WORLD);
int elem_por_proc = long_vec/size;
printf("Cantidad de elementos por procesador: %d\n", elem_por_proc);

MPI_Bcast(&sum,1,MPI_INT,0,MPI_COMM_WORLD);
vector_recv = (int*)malloc(sizeof(int) * elem_por_proc);
MPI_Scatter(vector, elem_por_proc, MPI_INT, vector_recv, elem_por_proc, MPI_INT, 0, MPI_COMM_WORLD);


for(i=0; i < elem_por_proc; i++) {
	printf("proc: %d, vec[%d]: %d\n", pid, i, vector_recv[i]);	
	vector_recv[i] = vector_recv[i] * sum;
}


MPI_Barrier(MPI_COMM_WORLD);
MPI_Gather(vector_recv, elem_por_proc, MPI_INT, result, elem_por_proc, MPI_INT, 0, MPI_COMM_WORLD);

if(pid == 0) {
	for(i=0; i<long_vec; i++){
		printf("posicion %d tiene %d\n", i, result[i]); 	
	}
}

return 0;
}
//Queda hacer un gather y mostrar

