#include<mpi.h>
#include<stdio.h>

int main(int argc , char ** argv ){
    int rank ,size ,ans ; 
    MPI_Comm World = MPI_COMM_WORLD;
    MPI_Status status ; 

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( World , &rank);
    MPI_Comm_size( World , &size);
    
    int arr[3][3],num;
    int chunk[3];
    if (rank==0){
        printf("Enter 3x3 Matrix \n");
        for (int i = 0 ; i  < 3 ; i++)
            for (int j=0 ; j < 3 ; j++)
                scanf("%d",&arr[i][j]);
        printf("Enter element to be searched \n ");
        scanf("%d",&num);
    }
    MPI_Bcast( &num , 1 , MPI_INT , 0 , World);
    MPI_Scatter( arr , 3 , MPI_INT , chunk , 3 , MPI_INT , 0 , World);
    int count = 0 ; 
    for (int i = 0 ; i < 3 ; i++)
        if (chunk[i]==num)
            count++;
    fprintf(stdout,"Count in Process %d is %d \n",rank,count);
    MPI_Reduce( &count , &ans , 1 , MPI_INT , MPI_SUM , 0 , World);
    fflush(stdout);
    if (rank==0)
    printf("Final number of occourences of %d is %d \n",num,ans);

    MPI_Finalize();
    return 0 ; 


}