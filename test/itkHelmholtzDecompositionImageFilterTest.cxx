#include "itkHelmholtzDecompositionImageFilter.h"
#include "itkTestingMacros.h"

int itkHelmholtzDecompositionImageFilterTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::HelmholtzDecompositionImageFilter< ImageType > FilterType;

  FilterType::Pointer filter = FilterType::New();

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType ); 

  return EXIT_SUCCESS;

}

