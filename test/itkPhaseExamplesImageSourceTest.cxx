#include "itkPhaseExamplesImageSource.h"
#include "itkTestingMacros.h"
#include "vnl/vnl_math.h"

int itkPhaseExamplesImageSourceTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::PhaseExamplesImageSource< ImageType > FilterType;
  
  FilterType::Pointer filter = FilterType::New();

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  TEST_SET_GET_VALUE( false, filter->GetShear() );
  filter->SetShear( true );
  TEST_SET_GET_VALUE( true, filter->GetShear() );

  TEST_SET_GET_VALUE( false, filter->GetNoise() );
  filter->SetNoise( true );
  TEST_SET_GET_VALUE( true, filter->GetNoise() );

  TEST_SET_GET_VALUE( vnl_math::pi / 2, filter->GetNoiseSD());
  filter->SetNoiseSD( 10.0 );
  TEST_SET_GET_VALUE( 10.0, filter->GetNoiseSD() );

  TEST_SET_GET_VALUE( 0.0, filter->GetNoiseMean() );
  filter->SetNoiseMean( 10.0 );
  TEST_SET_GET_VALUE( 10.0, filter->GetNoiseMean() );

  TEST_SET_GET_VALUE( 0, filter->GetNoiseSeed() );
  filter->SetNoiseSeed( 100 );
  TEST_SET_GET_VALUE( 100, filter->GetNoiseSeed() );

  TEST_SET_GET_VALUE( true, filter->GetWrap() );
  filter->SetWrap( false );
  TEST_SET_GET_VALUE( false, filter->GetWrap() );

  return EXIT_SUCCESS;

}
