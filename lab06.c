#include <mpi.h>
#include <stdio.h>

#define DEADLOCK_PART 1

int main(int argc, char *argv[])
{
    int rank, size, num = 123;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2) { if (rank == 0) printf("Run with at least 2 processes.\n"); MPI_Finalize(); return 0; }
#if DEADLOCK_PART == 1
    if (rank < 2)
    {
        printf("Process %d waiting...\n", rank);
        MPI_Recv(&num, 1, MPI_INT, 1 - rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&num, 1, MPI_INT, 1 - rank, 0, MPI_COMM_WORLD);
    }
#else
    if (rank == 0)
    {
        MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received: %d\n", num);
    }
    else if (rank == 1)
    {
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process 1 received and returned: %d\n", num);
    }
#endif
    MPI_Finalize();
    return 0;
}