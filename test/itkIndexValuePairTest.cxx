#include "itkIndexValuePair.h"
#include <string>
#include <iostream>
#include <cstdlib>

int itkIndexValuePairTest( int argc, char **argv ) {

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }

  typedef itk::IndexValuePair< std::string, int > PairType;

  PairType p1;
  p1.Index = "index";
  p1.Value = 0;

  PairType p2;
  p2.Index = "index";
  p1.Value = 1;

  if (!(p1.Index == p2.Index)) {
    std::cerr << "Failure on == operator test." << std::endl;
    return EXIT_FAILURE;
  }
  
  if (!(p1.Value < p2.Value)) {
    std::cerr << "Failure on < operator test." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
