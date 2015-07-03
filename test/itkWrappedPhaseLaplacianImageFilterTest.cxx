#include "itkWrappedPhaseLaplacianImageFilter.h"
#include "itkTestingMacros.h"

int itkWrappedPhaseLaplacianImageFilterTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::WrappedPhaseLaplacianImageFilter< ImageType > FilterType;
  
  FilterType::Pointer filter = FilterType::New();

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  TEST_SET_GET_VALUE( false, filter->GetWeighted() );
  filter->SetWeighted( true );
  TEST_SET_GET_VALUE( true, filter->GetWeighted() );  

  return EXIT_SUCCESS;

}
