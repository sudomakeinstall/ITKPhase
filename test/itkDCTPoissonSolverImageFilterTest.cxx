#include "itkDCTPoissonSolverImageFilter.h"
#include "itkTestingMacros.h"

int itkDCTPoissonSolverImageFilterTest(int argc, char **argv)
{
  
  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::DCTPoissonSolverImageFilter< ImageType > FilterType;
  
  FilterType::Pointer filter = FilterType::New();

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  // No properties to set.

  return EXIT_SUCCESS;

}
