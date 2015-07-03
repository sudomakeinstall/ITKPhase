#include "itkPhaseResidueImageFilter.h"
#include "itkTestingMacros.h"

int itkPhaseResidueImageFilterTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::PhaseResidueImageFilter< ImageType > FilterType;
  
  FilterType::Pointer filter = FilterType::New();

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
 
  // No methods.
 
  return EXIT_SUCCESS;

}
