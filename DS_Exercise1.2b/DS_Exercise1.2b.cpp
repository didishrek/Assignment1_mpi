#include <iostream>
#include <cstdlib>
#include <mpi.h>

int world_size;
int world_rank;

void master(){
  int size_of_array = 120000;
  int array[size_of_array];
  int array_sum[world_size - 1];

  for (int i = 0; i < size_of_array; i++){
    array[i] = rand() % 100;
  }


  for (int i = 0; i < world_size; i++){
    int tmp_array[24000];
    int start = 0;
    if (i == 1) continue;
    if (i == 2) start = 24000;
    if (i == 3) start = 48000;
    if (i == 4) start = 72000;
    if (i == 5) start = 96000;
    for (int j = start, k = 0; k < 24000; j++){
      tmp_array[k] = array[j];
      k++;
    }
    MPI_Send(&tmp_array, 24000, MPI_INT, i, 0, MPI_COMM_WORLD);
    int sum = 0;

    MPI_Recv(&sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    array_sum[i] = sum;
  }

  int sum = 0;
  for (int i = 0; i < world_size - 1 ; i++) {
    sum += array_sum[i];
  }
  std::cout << sum << std::endl;
}

void slave(){
  int array[24000];
  int sum = 0;
  MPI_Recv(&array, 24000, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  if (world_rank % 2 == 0){
    for (int i = 0 ; i < 12000; i++){
      sum += array[i];
    }
  } else {
    for (int i = 12000 ; i < 24000; i++){
      sum += array[i];
    }
  }

  std::cout << "node " << world_rank << " sum = " << sum << std::endl;
  MPI_Send(&sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

}

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  if (world_size != 6)
    return 1;

  if (world_rank == 1){
    master();
  } else {
    slave();
  }

  MPI_Finalize();
  return 0;
}
