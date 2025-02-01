#include<mpi.h>
#include<stdio.h>

int main(int argc , char ** argv ){
    int rank ,size ,ans ; 
    MPI_Comm World = MPI_COMM_WORLD;
    MPI_Status status ; 

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( World , &rank);
    MPI_Comm_size( World , &size);

    int arr[4][4],output[4][4],num;
    int chunk[4];
    int newChunk[4];
    if (rank==0){
        printf("Enter 4x4 Matrix \n");
        for (int i = 0 ; i  < 4 ; i++)
            for (int j=0 ; j < 4 ; j++)
                scanf("%d",&arr[i][j]);
        
    }
    MPI_Scatter( arr , 4 , MPI_INT , chunk , 4 , MPI_INT , 0 , World);

    MPI_Scan( chunk , newChunk , 4 , MPI_INT , MPI_SUM , World);

    MPI_Gather( newChunk , 4 , MPI_INT , output , 4 , MPI_INT , 0 , World);
    printf("\n");

    if (rank==0){
        
        for (int i = 0 ; i  < 4 ; i++){
            for (int j=0 ; j < 4 ; j++)
                printf("%d ",output[i][j]);
            printf("\n");
            }
            
    }

}