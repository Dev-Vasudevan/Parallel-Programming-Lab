#include "mpi.h"
#include <stdio.h>
int factorial(int n){
    if (n==1)return n ; 
    return n * factorial(n-1);
}
int main(int argc , char **argv){
    int size,rank , number , ans=0 ,fact  ;
    MPI_Comm World = MPI_COMM_WORLD;
    MPI_Status status ; 
    MPI_Init( &argc , &argv);
    MPI_Comm_rank( World , &rank);
    MPI_Comm_size( World , &size);
    int arr[size] , factorials[size];
    if (rank==0){
        printf("Enter %d numbers ",size);
        for (int i=0 ; i<size ; i++)
            scanf("%d",&arr[i]);
    }
        
    MPI_Scatter( arr , 1 , MPI_INT , &number , 1 , MPI_INT , 0 , World);
    fact = factorial(number);
    MPI_Gather( &fact , 1 , MPI_INT , &factorials , 1 , MPI_INT , 0 , World);
    if (rank==0){
        for (int i = 0 ; i < size ; i++){
            ans+=factorials[i];
            fprintf(stdout,"Factorial(%d) = %d \n",arr[i],factorials[i]);
        }
    fprintf(stdout,"Answer is %d \n",ans);
    }
    
    
        

    fflush(stdout);
    MPI_Finalize();
    return 0;


}