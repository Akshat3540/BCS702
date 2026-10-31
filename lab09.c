#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, value, r[4], a[4];
    MPI_Op op[4] = {MPI_SUM, MPI_PROD, MPI_MAX, MPI_MIN};
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    value = rank + 1;
    for (int i = 0; i < 4; i++)
    {
        MPI_Reduce(&value, &r[i], 1, MPI_INT, op[i], 0, MPI_COMM_WORLD);
        MPI_Allreduce(&value, &a[i], 1, MPI_INT, op[i], MPI_COMM_WORLD);
    }
    if (rank == 0)
    {
        printf("MPI_Reduce Results:\n");
        printf("Sum = %d\nProduct = %d\nMax = %d\nMin = %d\n", r[0], r[1], r[2], r[3]);
    }
    printf("Process %d: value=%d | Sum=%d Prod=%d Max=%d Min=%d\n", rank, value, a[0], a[1], a[2], a[3]);
    MPI_Finalize();
    return 0;
}