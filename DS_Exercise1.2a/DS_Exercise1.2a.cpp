#include <iostream>
#include <cstdlib>
#include <mpi.h>

int world_size;
int world_rank;

void master(){
  int size_of_array = 100000;
  int array[size_of_array];
  int array_sum[world_size - 1];
  //generate the array.
  for (int i = 0; i < size_of_array; i++){
    array[i] = rand() % 100;
  }

  // for each node
  for (int i = 1; i < world_size; i++){
    int tmp_array[20000];
    int start = 0;
    if (i == 2) start = 20000;
    if (i == 3) start = 40000;
    if (i == 4) start = 60000;
    if (i == 5) start = 80000;
    for (int j = start, k = 0; k < 20000; j++){ // copy of a part of the big array into little array
      tmp_array[k] = array[j];
      k++;
    }
    MPI_Send(&tmp_array, 20000, MPI_INT, i, 0, MPI_COMM_WORLD); // send array
    int sum = 0;

    MPI_Recv(&sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //receive sum
    array_sum[i - 1] = sum;
  }

  int sum = 0;
  for (int i = 0; i < world_size - 1 ; i++) { // make sum of sums
    sum += array_sum[i];
  }
  std::cout << sum << std::endl; //display sum
}

void slave(){
  int array[20000];
  int sum = 0;
  MPI_Recv(&array, 20000, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive a little array

  for (int i = 0 ; i < 20000; i++){
    sum += array[i]; // add all numbers
  }
  std::cout << "node " << world_rank << " sum = " << sum << std::endl;
  MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); //send sum

}

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  if (world_size != 6)
    return 1;

  if (world_rank == 0){
    master();
  } else {
    slave();
  }

  MPI_Finalize();
  return 0;
}
