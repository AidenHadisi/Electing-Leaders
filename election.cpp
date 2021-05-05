#include <iostream>
#include <string>
#include "mpi.h"
#include "time.h"
using namespace std;

// Concats integers as described in program requirements
// "1" + randomNumber + rank
int concatInts(int, int, int);

//Creates a random int between 10 and 100, concats them according to problem definition.
int computeValues(int);


int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);



  // [President, VicePresiden]
  // [Odd, Even]
  int results[2];

  int random = computeValues(rank);


  printf("This is the process %d and my rand is %d\n", rank, random);

  if(rank > 0) {
    MPI_Recv(&results, 2, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if(random % 2 == 1) {
      if(random > results[0]) results[0] = random;
    }
    else {
      if(random > results[1]) results[1] = random;
    }
    printf("Process %d recieved values [%d, %d]\n", rank, results[0], results[1]);
  }
  else {
    if(random % 2 == 0) {
      results[1] = random;
      results[0] = 1;
    }
    else {
      results[0] = random;
      results[1] = 0;
    }

  }

  MPI_Send(&results, 2, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
  if(rank == 0) {
    MPI_Recv(&results, 2, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("The president is %d and the vice president is %d\n", results[0], results[1]);
  }




  MPI_Finalize();
  return 0;


}
int concatInts(int a, int b, int c)
{
    string s1 = to_string(a);
    string s2 = to_string(b);
    string s3 = to_string(c);
    string s = s1 + s2 + s3;
    int result = stoi(s);
    return result;
}

int computeValues(int rank) {
  srand((unsigned) time(NULL) + rank);
  int random = rand() % 90 + 10;
  random = concatInts(1, random, rank);

  return random;
}
