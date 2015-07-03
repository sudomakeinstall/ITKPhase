#include "itkPhaseQualityImageFilter.h"
#include "itkTestingMacros.h"

int itkPhaseQualityImageFilterTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::PhaseQualityImageFilter< ImageType > FilterType;
  
  FilterType::Pointer filter = FilterType::New();

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////

  TEST_SET_GET_VALUE( false, filter->GetThreshold() );
  filter->SetThreshold( true );
  TEST_SET_GET_VALUE( true, filter->GetThreshold() );  

  TEST_SET_GET_VALUE( 0.75, filter->GetThresholdValue() );
  filter->SetThresholdValue( 0.8 );
  TEST_SET_GET_VALUE( 0.8, filter->GetThresholdValue() );

  TEST_SET_GET_VALUE( FilterType::PhaseDerivativeVariance, filter->GetQualityMetric() );

  return EXIT_SUCCESS;

}
