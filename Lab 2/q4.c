#include<mpi.h>
#include<stdio.h>
int main (int argv , char * argc[] ){
    int rank , size ; 
    MPI_Comm world = MPI_COMM_WORLD ; 
    MPI_Init( &argv , &argc);
    
    MPI_Comm_rank( world , &rank);
    MPI_Comm_size( world , &size);
    MPI_Status status ; 
    int num ; 
    printf("Rank %d %d \n",rank,size);
    

    if (rank==0){
        scanf("%d",&num);
        MPI_Send( &num , 1 , MPI_INT , (rank+1)%size , 0 , world);
        fprintf(stdout,"Rank : %d num : %d \n" ,rank,num);
        MPI_Recv( &num , 1 , MPI_INT , size-1 , 0 , world , &status);
        fprintf(stdout,"Rank : %d num : %d \n" ,rank,num);
        }
    else { 
        
        MPI_Recv( &num , 1 , MPI_INT , (rank-1)%size , 0 , world , &status);
        num+=1;
        MPI_Send( &num , 1 , MPI_INT , (rank+1)%size , 0 , world);
        fprintf(stdout,"Rank : %d num : %d \n",rank,num);
    }

    
    
    
            
    // }
    // else {
    //     MPI_Recv( &num , 1 , MPI_INT , 0 , 0 , world , &status);
    //     if (rank%2){
            
    //         fprintf(stdout , "Rank : %d , %d^3 : %f ",rank ,num, pow(num,3));
    //         }
    //     else {
    //         fprintf(stdout , "Rank : %d , %d^2 : %f ",rank ,num, pow(num,2));
    //         }

    // }
    fflush(stdout);
    MPI_Finalize();
    return 0 ;
}