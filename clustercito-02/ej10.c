/**
Escribe la versión paralela del programa matvecser.c, que efectúa el siguiente cálculo con
matrices y vectores.
double A(NxN), B(N), C(N), D(N), X
C(N) = A(NxN) × B(N)
D(N) = A(NxN) × C(N)
X = C(N).D(N)
El programa pide al principio el tamaño de los vectores, N.
Inicialmente, A y B están en el proceso P0; al final, C, D y X tienen que quedar en P0.
**/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define N 16

void printarr(int **data, int n, char *str);

int **allocarray(int n);

int main(int argc, char **argv) {
    /* array sizes */
    const int arraysize =N;
    const int matrizsize=N;
    /* comunication params */
    const int sender=0;
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // pid id
    MPI_Comm_size(MPI_COMM_WORLD, &size); //procesos disponibles
 
    int **subarray = allocarray(array);   
    if (rank == sender) { // si el pid es igual a 0
        //declara una matriz y le asigna valores
        int **matriz = allocarray(matriz);
        int i,j;
        int sum=0;
        for (i=0; i<matrizsize; i++){
            for (j=0; j<matrizsize; j++){
                matriz[i][j] = rand() % 20;
            }
        }
        
        printarr(matriz, matrizsize, " Send: matriz");
        
        MPI_Datatype mysubarray; //declara el datatype
        int arraysizes[2]  = {1,arraysize}; // {5,5}
        int matrizsizes[2]  = {matrizsize, matrizsize};// {10,10}
        
        int starts[4][2]= {
            {0,0}, 
            {1,0},
            {2,0},
            {3,0}
        };
        
        for (i=0; i<4; i++) {              
            MPI_Type_create_subarray(
                2,
                matrizsizes,
                arraysizes,
                starts[i],
                MPI_ORDER_C,
                MPI_INT,
                &mysubarray
            );
            MPI_Type_commit(&mysubarray);
            
            if(i != 0) {
                MPI_Send(
                    &(matriz[0][0]), //elemento a enviar
                    1, //cantidad de elementos 
                    mysubarray, //tipo de elemento
                    i, //Rank
                    ourtag, //tag 
                    MPI_COMM_WORLD
                );
            }
        }
    }
    
    if(rank != 0) {
        int i;
            for (i=0; j<arraysize; i++) {
                subarray[i]= 0;
            }

        MPI_Recv(
            &(subarray[0]),//elemento que recibo
            arraysize, //cantidad de datos que recibo (elementos de la matriz)
            MPI_INT,//tipo de elementos de la matriz
            sender, //rank del que me envio el mensaje
            ourtag, //un tag
            MPI_COMM_WORLD, //mundo de los procesos
            MPI_STATUS_IGNORE
        ); //ignora los estados de errores
    }
    MPI_Barrier(MPI_COMM_WORLD);
    
    printarr(subarray, arraysize, "Receiver: Subarray -- after receive\n");
    int sumatoria = sumMatriz(subarray,arraysize);
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

int **allocarray(int n) {
    int *data = malloc(n*n*sizeof(int));
    int **arr = malloc(n*sizeof(int *));
    int i;
    for (i=0; i<n; i++)
        arr[i] = &(data[i*n]);

    return arr;
}
