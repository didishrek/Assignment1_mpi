#include <iostream>
#include <cstdlib>
#include <mpi.h>

int world_size;
int world_rank;

void display_array(int array[], int size_of_array){
  std::cout << "[ ";
  for (int i = 0; i < size_of_array; ++i){
    std::cout << array[i] << " ";
  }
  std::cout << "]" << std::endl;
}

void master(){
  int size_of_array = 200;
  int array[size_of_array];
  int number_to_generate;
  int rest_plus_number_to_generate;
  int current_index = 0;

  number_to_generate = size_of_array / (world_size - 1);
  rest_plus_number_to_generate = (size_of_array % (world_size - 1)) + number_to_generate;

  for (int i = 1; i < world_size; i++){
    if (i == 1){
      int tmp_array[rest_plus_number_to_generate];
      MPI_Send(&rest_plus_number_to_generate, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Recv(&tmp_array, rest_plus_number_to_generate, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      for (int j = current_index, k = 0; k < rest_plus_number_to_generate; ++j, k++){
        array[j] = tmp_array[k];
        current_index ++;
      }
    }
    else{
      int tmp_array[number_to_generate];
      MPI_Send(&number_to_generate, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Recv(&tmp_array, number_to_generate, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      for (int j = current_index, k = 0; k < number_to_generate; ++j, k++){
        array[j] = tmp_array[k];
        current_index ++ ;
      }
    }
  }
  display_array(array, size_of_array);
}

void slave(){
  int number_to_generate = 0;

  MPI_Recv(&number_to_generate, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  int array[number_to_generate];

  std::cout << "node " << world_rank << " : ";

  for(int i = 0; i < number_to_generate; ++i){
    array[i] = rand() % 100;
  }
  display_array(array, number_to_generate);
  MPI_Send(&array, number_to_generate, MPI_INT, 0, 0, MPI_COMM_WORLD);
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (world_rank == 0){
    master();
  } else {
    slave();
  }

  MPI_Finalize();
  return 0;
}
