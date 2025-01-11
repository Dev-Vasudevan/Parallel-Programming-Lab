#include<mpi.h>
#include<stdio.h>
#include<math.h>
int main (int argv , char * argc[] ){
    int rank , size ; 
    MPI_Comm world = MPI_COMM_WORLD ; 
    MPI_Init( &argv , &argc);
    
    MPI_Comm_rank( world , &rank);
    MPI_Comm_size( world , &size);
    MPI_Status status ; 
    int num ; 
    printf("Rank %d",rank);
    if (rank==0){
        for (int i = 1 ; i < size ; i++){
            scanf("%d",&num);
            MPI_Send( &num , 1 , MPI_INT , i , 0 , world);
        }
            
    }
    else {
        MPI_Recv( &num , 1 , MPI_INT , 0 , 0 , world , &status);
        if (rank%2){
            
            fprintf(stdout , "Rank : %d , %d^3 : %f ",rank ,num, pow(num,3));
            }
        else {
            fprintf(stdout , "Rank : %d , %d^2 : %f ",rank ,num, pow(num,2));
            }

    }
    fflush(stdout);
    MPI_Finalize();
    return 0 ;
}