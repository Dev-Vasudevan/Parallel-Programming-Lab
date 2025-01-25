#include<mpi.h>
#include<stdio.h>
#include<string.h>
int isVowel(char c){
    char vows[5] = {'a','e','i','o','u'};
    for (int i = 0 ; i < 5 ; i++)
        if (vows[i]==c)
            return 1; 
    return 0 ; 
}
int main(int argc , char ** argv ){
    char str[100];
    int rank ,size , n , count = 0 ,ans=0; 
    MPI_Comm World = MPI_COMM_WORLD;
    MPI_Status status ; 

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( World , &rank);
    MPI_Comm_size( World , &size);
    int  vowels[size];

    if (rank==0){
        fgets(str,100,stdin);
        n = strlen(str)/size;
        
    }
    MPI_Bcast( &n , 1 , MPI_INT , 0 , World);
    char chunk[n+1];

    MPI_Scatter( str , n , MPI_CHAR , chunk , n , MPI_CHAR , 0 , World);
    
    for (int i=0 ; i < n ; i++){
        if (isVowel(chunk[i]))
            count+=1 ;
    }
    MPI_Gather( &count , 1 , MPI_INT , vowels , 1 , MPI_INT , 0 , World);

    if (rank==0){
        for (int i = 0 ; i < size ; i++)
        {
            printf("Vowels in the %d Chunk are : %d \n",i+1 , vowels[i]);
            ans+=vowels[i];
        }
        printf("Answer is %d",ans);
    }




}
