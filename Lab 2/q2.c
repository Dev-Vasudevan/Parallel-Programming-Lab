#include<mpi.h> 
#include<stdio.h> 

int main (int argv , char * argc[]){
    MPI_Init( &argv , &argc);
    int rank , size ; 
    MPI_Comm world = MPI_COMM_WORLD ; 
    MPI_Comm_rank( world , &rank);
    MPI_Comm_size(world , &size);
    MPI_Status status ; 
    int num ;
    if (rank==0){
        scanf("%d",&num);
        for (int i=1 ; i < size ; i++){
            MPI_Send( &num, 1 , MPI_INT , i , 0 , MPI_COMM_WORLD);
        }

    }
    else{
        MPI_Recv( &num , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &status); 
        fprintf(stdout ,"Rank : %d , val : %d ",rank,num);
        
    }
    fflush(stdout);

    MPI_Finalize();
    return 0 ;
}