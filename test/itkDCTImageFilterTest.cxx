#include "itkDCTImageFilter.h"
#include "itkTestingMacros.h"

int itkDCTImageFilterTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::DCTImageFilter< ImageType > FilterType;
  
  FilterType::Pointer filter = FilterType::New();

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  TEST_SET_GET_VALUE( FilterType::Forward, filter->GetTransformDirection() );
  filter->SetTransformDirection( FilterType::Reverse );
  TEST_SET_GET_VALUE( FilterType::Reverse, filter->GetTransformDirection() );  

  return EXIT_SUCCESS;

}

