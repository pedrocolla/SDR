#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv){

    int node;
    char cpuname[20];
    int  cpulen;
    MPI_Init(&argc, &argv);


    MPI_Comm_rank(MPI_COMM_WORLD, &node);
    MPI_Get_processor_name( cpuname, &cpulen );
 
    printf("[%s] Saludos desde el esclavo (%d)!\n", cpuname,node);
    
    MPI_Finalize();
}
