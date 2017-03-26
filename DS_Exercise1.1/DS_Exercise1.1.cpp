#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
  int world_size;
  int world_rank;

  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (world_size == 4){ // display datas if world_size == 4
    std::cout << "Student name : Adrien SCHRICKE" << std::endl;
    std::cout << "Student number : 2927372" << std::endl;

    std::cout << "number of processor: " << world_size << std::endl; // number of nodes

    std::cout << "rank is: " << world_rank << std::endl; // number of the node
  }

  MPI_Finalize();
  return 0;
}
