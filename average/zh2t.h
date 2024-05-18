#include <mpi.h>
#include <stdio.h>

int main() {
    MPI_Init(NULL, NULL);
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a[50]; // local array of 50 elements
    int i;
    // Initialize the local array with some values
    for (i = 0; i < 50; i++) {
        a[i] = rank * 50 + i; // Example initialization: distinct values for each process
    }

    int mysum = 0;
    for (i = 0; i < 50; i++) {
        mysum += a[i];
    }

    int totalsum = 0;

    // Reduce all local sums to the root process (rank 0)
    MPI_Reduce(&mysum, &totalsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int total_elements = 50 * size; // total number of elements in the global array
        double average = (double)totalsum / total_elements;
        printf("Total sum: %d, Average: %f\n", totalsum, average);
    }

    MPI_Finalize();
    return 0;
}
