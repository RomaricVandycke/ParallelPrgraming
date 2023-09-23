// Example For 4 MPI tasks

/*     			  P0   P1   P2   P3
myid              0    1    2    3
myidvec	   		  3    0    1    2  
myidvec+myid      3    1    3    5  */


#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{

    MPI_Status info;
    int myid, npes, src, dest, myidvec;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&npes);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    src = myid-1;
    dest = myid+1;
    if (src < 0)
	src += npes;
    if (dest >= npes)
	dest -= npes;

    MPI_Sendrecv(&myid, 1, MPI_INT, dest, 6, &myidvec, 1, MPI_INT, src, 6, MPI_COMM_WORLD, &info);

    printf("I am %d and I received %d\n", myid, myidvec + myid);

    MPI_Finalize();
}

