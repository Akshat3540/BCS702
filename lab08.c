#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size, data[100], recv_data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for (int i = 0; i < size; i++) data[i] = i * 10;
    MPI_Scatter(data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    recv_data += rank;
    MPI_Gather(&recv_data, 1, MPI_INT, data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Gathered data:\n");
        for (int i = 0; i < size; i++) printf("%d\n", data[i]);
    }
    MPI_Finalize();
    return 0;
}