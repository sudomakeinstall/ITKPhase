#include "itkItohPhaseUnwrappingImageFilter.h"
#include "itkTestingMacros.h"

int itkItohPhaseUnwrappingImageFilterTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ItohPhaseUnwrappingImageFilter< ImageType > FilterType;
  
  FilterType::Pointer filter = FilterType::New();

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  TEST_SET_GET_VALUE( 0, filter->GetDirection() );
  filter->SetDirection( 1 );
  TEST_SET_GET_VALUE( 1, filter->GetDirection() ); 

  return EXIT_SUCCESS;

}


