#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int *createMatrix (int nrows, int ncols) {

    int *matrix;
    int h, i, j;

    for (h=0; h<nrows*ncols; h++) {
        matrix[h] = h+1;
    }
    return matrix; //la piel se amolda al sistema
}

void printArray (int *row, int nElements) {
    int i;
    for (i=0; i<nElements; i++) {
        printf("%d ", row[i]);
    }
    printf("\n");
}

int sumArray (int *row, int nElements) {
    int i;
	int sumatoria =0;
    for (i=0; i<nElements; i++) {
         sumatoria = row[i] + sumatoria;
    }
	printf("%d",sumatoria);
  printf("\n");
   return sumatoria;
}


int main (int argc, char **argv) {

   	int p, id;
    int *matrix;
	int *rbuf =0; 
    int *procRow = malloc(sizeof(int) * p); // received row will contain p integers

    MPI_Comm_size(MPI_COMM_WORLD, &p); // Get number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &id); // Get own ID
	
    if (id == 0) {
        matrix = createMatrix(p, p); // Master process creates matrix
        printf("Initial matrix:\n");
        printArray(matrix, p*p);
		printArray(rbuf,4);
		rbuf = (int *)malloc(sizeof(int)); 
    }



	if (id != 0 ){
			int resultado = sumArray(procRow,p);
			printf("%d",resultado);			
	}

    MPI_Scatter(matrix, 
				p, 
				MPI_INT, // send one row, which contains p integers
                procRow, 
				p, 
				MPI_INT, // receive one row, which contains p integers
                0, 
				MPI_COMM_WORLD) 
	
    printf("Process %d received elements: ", id);
    printArray(procRow, p);

    MPI_Finalize();

    return 0;
}
