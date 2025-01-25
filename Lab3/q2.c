#include<mpi.h>
#include<stdio.h>

int main(int argc , char ** argv ){
    int size,rank   ,n  ;
    float avg=0, ans=0;

    MPI_Comm World = MPI_COMM_WORLD;
    MPI_Status status ; 
    MPI_Init( &argc , &argv);
    MPI_Comm_rank( World , &rank);
    MPI_Comm_size( World , &size);
    float averages[size];
    if (rank==0){
        printf("Enter 'n'  of elements in form %d x n",size);
        scanf("%d",&n);
    }
    // First sending n 
    MPI_Bcast( &n , 1 , MPI_INT , 0 , World);
    int arr[n*size];
    int small[n];

    if (rank==0){
        for (int i = 0 ; i < n*size ; i++){
            scanf("%d" , &arr[i]);
        }
    }
    
    // Sending broken array 
    MPI_Scatter( arr , n , MPI_INT , small , n , MPI_INT , 0 , World);

    for(int i = 0 ; i < n ; i++)
        avg+=small[i];
    avg/=n;

    MPI_Gather( &avg , 1 , MPI_FLOAT , averages , 1 , MPI_FLOAT , 0 , World);

    if(rank==0){

        for(int i = 0 ; i < size ; i++){
            fprintf(stdout, "%d Average is %f\n",i+1 , averages[i]);
            ans+=averages[i];
        }
        ans/=size; 
        fprintf(stdout,"Total Average is %f",ans);
    }

    MPI_Finalize();
    fflush(stdout);
    return 0 ; 


}