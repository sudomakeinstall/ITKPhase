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

#include "itkQualityGuidedPhaseUnwrappingImageFilter.h"
#include "itkPhaseQualityImageFilter.h"
#include "itkTestingMacros.h"

int itkQualityGuidedPhaseUnwrappingImageFilterTest(int argc, char **argv)
{

  if (1 != argc)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::PhaseQualityImageFilter< ImageType >                 QualityType;
  typedef itk::QualityGuidedPhaseUnwrappingImageFilter< ImageType > FilterType;

  QualityType::Pointer quality = QualityType::New();
  FilterType::Pointer filter = FilterType::New();

  ImageType::IndexType index;
  index.Fill( 10 );

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType, FilterType::Superclass ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  TEST_SET_GET_VALUE( index, filter->GetTruePhase() );

  //
  return EXIT_SUCCESS;

}
