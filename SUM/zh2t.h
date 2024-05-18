#include <iostream>
#include <mpi.h>
using namespace std;
#define veclen 100
int main()
{
	MPI_Init(NULL, NULL);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int data[15];

	int localsum = 0;
	int localdata[5];
	int sums[8] = { 0,0,0 };
	int finalsum = 0;

	if (rank == 0) {


		for (int i = 0; i < 15; i++) {
			data[i] = i+1;

		}
		cout << "data generated" << endl;

	}

	MPI_Scatter(&data, 5, MPI_INT, &localdata, 5, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < 5; i++) {
		localsum = localsum + localdata[i];

	}
	//cout << "local sum of = " << localsum << endl;


	MPI_Gather(&localsum, 1, MPI_INT, &sums, 1, MPI_INT, 0, MPI_COMM_WORLD);



	if (rank == 0) {


		for (int i = 0; i < 3; i++) {
			finalsum = finalsum + sums[i];
		}


		cout << "finaaaaaaaaaaaaaaal sum = " << finalsum;
	}

	MPI_Finalize();

	return 0;


}