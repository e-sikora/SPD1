// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <iostream>

#include "problem.h"

int main(int argc, char *argv[]) {
  if(argc!=2){
    std::cout << "Błędne wywołanie programu! Program kończy działanie!" << std::endl;
    exit(EXIT_FAILURE);
  }

  Problem<Item<int>> problem;
  problem.loadFromFile(argv[1]);

  //problem.permutationSort();
  problem.occurTimeSort();
  problem.idleTimeSort();
  problem.schrageAlgorithmV1();
  problem.schrageAlgorithmV2();
  problem.schrageAlgorithmWithExpropriation();
  problem.bisoraAlgorithm();

  return 0;
}
