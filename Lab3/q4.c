#include<mpi.h>
#include<stdio.h>
#include<string.h>

int main(int argc , char ** argv ){
    char str1[100];
    char str2[100];
    char ans[200];
    int rank ,size , n , count = 0 ; 
    MPI_Comm World = MPI_COMM_WORLD;
    MPI_Status status ; 

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( World , &rank);
    MPI_Comm_size( World , &size);

    if (rank==0){
        fgets(str1,100,stdin);
        fgets(str2,100,stdin);
        n = strlen(str1)/size;
    }
    MPI_Bcast( &n , 1 , MPI_INT , 0 , World);
    char chunk1[n+1];
    char chunk2[n+1];
    MPI_Scatter( str1 , n , MPI_CHAR , chunk1 , n , MPI_CHAR , 0 , World);
    MPI_Scatter( str2 , n , MPI_CHAR , chunk2 , n , MPI_CHAR , 0 , World);
    char bigChunk[2*n+1];
    for (int i=0 ; i < n ; i++){
        bigChunk[i*2]=chunk1[i];
        bigChunk[i*2+1]=chunk2[i];
    }
    MPI_Gather( bigChunk , 2*n , MPI_CHAR , ans , 2*n , MPI_CHAR , 0 , World);
    if (rank==0)
        printf("%s",ans);
    MPI_Finalize();
    return 0 ; 




}