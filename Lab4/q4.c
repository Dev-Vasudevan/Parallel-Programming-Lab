#include<mpi.h>
#include<stdio.h>
#include<string.h> 

int main(int argc , char ** argv ){
    int rank ,size ,ans ; 
    MPI_Comm World = MPI_COMM_WORLD;
    MPI_Status status ; 

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( World , &rank);
    MPI_Comm_size( World , &size);

    char st[100], ch , output[10000] , temp[100];

    if (rank==0){
        printf("Enter String of length %d",size);
        fgets(st,100,stdin);
    }

    MPI_Scatter( st , 1 , MPI_CHAR , &ch , 1 , MPI_CHAR , 0 , World);

    for (int i = 0 ; i <= rank; i++)
        temp[i]=ch;
    temp[rank+1]='\0';

    printf("Rank is %d , st is ",rank);
    fprintf(stdout, "%s \n",temp);

    
    if (rank==0){
        printf("Entered if \n");
        output[0] = ch ; 
        int pt = 1 ;
        for (int i = 1 ; i < size ; i++){
            printf("Trying to revice\n");
            MPI_Recv( output+pt , i+1 , MPI_CHAR , 0 , 1 , World , &status);
            pt+= (i+1);
            printf("%s",output);
        }
        output[pt]='\0';
        printf("%s",output);
    }
    else { 
        MPI_Send( temp , rank+1 , MPI_CHAR , 0 , 1 , World);
    }
    // MPI_Gather( temp , rank , MPI_CHAR , output , rank , MPI_CHAR , 0 , World);
    // if (rank==0)
        
    MPI_Finalize();



}