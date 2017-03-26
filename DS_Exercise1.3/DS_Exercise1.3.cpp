#include <iostream>
#include <cstdlib>
#include <mpi.h>

#define SIZE_OF_ARRAY (200)

// this function display an array of int in the console.
void display_array(int array[], int size_of_array){
  std::cout << "[ ";
  for (int i = 0; i < size_of_array; ++i){
    std::cout << array[i] << " ";
  }
  std::cout << "]" << std::endl;
}


void slave(int world_rank, int world_size) {
  int subarray_size = (SIZE_OF_ARRAY / world_size);
  int *subarray = new int[subarray_size];

  srand(world_rank);
  for(unsigned int i = 0; i < subarray_size; i++) //fill the array
    subarray[i] = rand() % 1000;
  std::cout << "node number " << world_rank << "'s datas : ";
  display_array(subarray, subarray_size);
  MPI_Gather(&subarray_size, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD); // send the size of the array to node 0
  MPI_Gatherv(subarray, subarray_size, MPI_INT, NULL, NULL, NULL, MPI_INT, 0, MPI_COMM_WORLD); // send the array to node 0

  delete subarray;
}


void master(int world_rank, int world_size) {
  int subarray_size = (SIZE_OF_ARRAY / world_size)  + (SIZE_OF_ARRAY % world_size);//generate an array that can be bigger to stock the rest of the division
  int *subarray = new int[subarray_size];
  int *num_array = new int[SIZE_OF_ARRAY];
  int *lengths_array = new int[world_size];
  int *offsets_array = new int[world_size];

  for(unsigned int i = 0; i < subarray_size; i++)
    subarray[i] = rand() % 1000; // generate the array like the slaves
  std::cout << "node number " << world_rank << "'s datas : ";
  display_array(subarray, subarray_size);

  MPI_Gather(&subarray_size, 1, MPI_INT, lengths_array, 1, MPI_INT, 0, MPI_COMM_WORLD);
  std::cout << "node number " << world_rank << " recieved : "; // receives and display the different sizes of arrays generated
  display_array(lengths_array, world_size);

  offsets_array[0] = 0;
  for(unsigned int i = 1; i < world_size; i++) // fill this array with the index of where start each array coming from slaves
  offsets_array[i] = offsets_array[i-1] + lengths_array[i-1];
  MPI_Gatherv(subarray, subarray_size, MPI_INT, num_array, lengths_array, offsets_array, MPI_INT, 0, MPI_COMM_WORLD); // receive and concat all arrays into num_array
  std::cout << "[MASTER] DATAS : ";
  display_array(num_array, SIZE_OF_ARRAY); //display num_array

  delete lengths_array;
  delete subarray;
  delete num_array;
}

int main(int argc, char **argv) {
  MPI_Init(NULL, NULL);
  int world_size, world_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  if(world_rank == 0)
    master(world_rank, world_size);
  else
    slave(world_rank, world_size);
  MPI_Finalize();
}
