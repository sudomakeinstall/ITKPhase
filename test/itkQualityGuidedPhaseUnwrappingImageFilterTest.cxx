#include "itkQualityGuidedPhaseUnwrappingImageFilter.h"
#include "itkTestingMacros.h"

int itkQualityGuidedPhaseUnwrappingImageFilterTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::QualityGuidedPhaseUnwrappingImageFilter< ImageType > FilterType;
  
  FilterType::Pointer filter = FilterType::New();

  ImageType::IndexType index;
  index.Fill( 10 );

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  TEST_SET_GET_VALUE( index, filter->GetTruePhase() );

  return EXIT_SUCCESS;

}


