#include <iostream>
#include <mpi.h>
#include<stdio.h>
using namespace std;
#define veclen 100
int main()
{
	MPI_Init(NULL, NULL);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int data1[veclen];
	int data2[veclen];

	if (rank == 0)
	{
		for (int i = 0; i < veclen; i++)
		{
			data1[i] = 2;
			data2[i] = 3;

		}
	}

	int* sub1 = new int[veclen / size];
	int* sub2 = new int[veclen / size];

	MPI_Scatter(&data1, veclen / size, MPI_INT, sub1, veclen / size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(&data2, veclen / size, MPI_INT, sub2, veclen / size, MPI_INT, 0, MPI_COMM_WORLD);


	int sum = 0;
	for (int i = 0; i < veclen / size; i++)
	{
		sum += sub1[i] * sub2[i];
	}
	int* sums = new int[size];

	MPI_Gather(&sum, 1, MPI_INT, sums, 1, MPI_INT, 0, MPI_COMM_WORLD);


	if (rank == 0) {
		int final = 0;
		for (int i = 0; i < size; i++) {
			final += sums[i];
		}
		for (int i = ((veclen / size) * size); i < veclen; i++) {

			final += (data1[i] * data2[i]);
		}

		cout << final << endl;
	}

	MPI_Finalize();

}