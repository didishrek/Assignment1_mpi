#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <iomanip>

int world_size;
int world_rank;

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (world_size < 10)
  return 1;

  //use the code given in github
  int n, i;
	double pi, h, sum, x, total_sum;
	n = 10000000;
	h = 1.0 / (double) n;
	sum = 0.0;
	for (i = 1; i <= n; i++) {
		x = h * ((double)i - 0.5);
		sum += 4.0 / (1.0 + x*x);
	}
    pi = sum / n;

  //Use reduce to get the sum of all pi calculated.
  MPI_Reduce(&pi, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  std::cout << "rank " << world_rank << " pi : " << std::setprecision(30) << pi << std::endl;

  if (world_rank == 0){ // on the "master" node : display the average of all pi calculated
    std::cout << std::setprecision(30) << (total_sum / world_size) << std::endl;
  }


  MPI_Finalize();
  return 0;
}
