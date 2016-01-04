/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

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
