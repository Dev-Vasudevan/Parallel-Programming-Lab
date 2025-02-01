#include<mpi.h>
#include<stdio.h>

int main(int argc , char ** argv ){
    int rank ,size ,ans ; 
    MPI_Comm World = MPI_COMM_WORLD;
    MPI_Status status ; 

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( World , &rank);
    MPI_Comm_size( World , &size);

    int fact , num=rank+1 ; 

    MPI_Scan( &num , &fact , 1 , MPI_INT , MPI_PROD , World);
    fprintf(stdout, "Rank %d, factorial %d \n",rank,fact);
    MPI_Reduce( &fact , &ans , 1 , MPI_INT , MPI_SUM , 0 , World);
    if (rank==0)
        printf("Final answer is %d",ans);


    MPI_Finalize();
    return 0 ; 

}