#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define N 16

void printarr(int **data, int n, char *str);

int **allocarray(int n);

int main(int argc, char **argv) {
    /* array sizes */
    const int bigsize =N;
    const int subsize =N/2;
    
    /* communications parameters */
    const int sender  =0;
    const int ourtag  =2;
    
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // pid id
    MPI_Comm_size(MPI_COMM_WORLD, &size); //procesos disponibles
    int **subarray = allocarray(subsize);
    
    if (rank == sender) { // si el pid es igual a 0
        //declara una matriz y le asigna valores
        int **bigarray = allocarray(bigsize);
        int i,j;
        int sum=0;
        for (i=0; i<bigsize; i++){
            for (j=0; j<bigsize; j++){
                bigarray[i][j] = rand() % 20;
            }
        }
        
        printarr(bigarray, bigsize, " Send: Bigarray");
        
        MPI_Datatype mysubarray; //declara el datatype
        int subsizes[2]  = {subsize,subsize}; // {5,5}
        int bigsizes[2]  = {bigsize, bigsize};// {10,10}
        
        int starts[4][2]= {
            {0, 0}, 
            {0,subsize},
            {subsize,0},
            {subsize,subsize}
        };
        
        for (i=0; i<4; i++) {              
            MPI_Type_create_subarray(
                2,
                bigsizes,
                subsizes,
                starts[i],
                MPI_ORDER_C,
                MPI_INT,
                &mysubarray
            );
            MPI_Type_commit(&mysubarray);
            
            if(i != 0) {
                MPI_Send(
                    &(bigarray[0][0]), //elemento a enviar
                    1, //cantidad de elementos 
                    mysubarray, //tipo de elemento
                    i, //Rank
                    ourtag, //tag 
                    MPI_COMM_WORLD
                );
            }
        }

        for (i=0; i<subsize; i++) {
            for (j=0; j<subsize; j++) {
                subarray[i][j] = bigarray[i][j];
            }
        }
    }
    
    if(rank != 0) {
        int i, j;
        for (i=0; i<subsize; i++) {
            for (j=0; j<subsize; j++) {
                subarray[i][j] = 0;
            }
        }

        MPI_Recv(
            &(subarray[0][0]),//elemento que recibo
            subsize*subsize, //cantidad de datos que recibo (elementos de la matriz)
            MPI_INT,//tipo de elementos de la matriz
            sender, //rank del que me envio el mensaje
            ourtag, //un tag
            MPI_COMM_WORLD, //mundo de los procesos
            MPI_STATUS_IGNORE
        ); //ignora los estados de errores
    }
    printf("hola");
    
    printarr(subarray, subsize, "Receiver: Subarray -- after receive\n");
    int sumatoria = sumMatriz(subarray,subsize);
    printf("Suma de matriz para proceso %d = %d\n",rank, sumatoria);        
    
    int total = 0;
    MPI_Reduce(&sumatoria, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
        printf("Suma Total: %d\n", total); 

    MPI_Finalize();
    return 0;
}

void printarr(int **data, int n, char *str) {    
    printf("-- %s --\n", str);
    int i,j;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%3d ", data[i][j]);
        }
        printf("\n");
    }
}
int sumMatriz(int **data, int n) {    
    int sumatoria =0;
    int i,j;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            sumatoria += data[i][j];
        }
    }
    return sumatoria;
}

int **allocarray(int n) {
    int *data = malloc(n*n*sizeof(int));
    int **arr = malloc(n*sizeof(int *));
    int i;
    for (i=0; i<n; i++)
        arr[i] = &(data[i*n]);

    return arr;
}
