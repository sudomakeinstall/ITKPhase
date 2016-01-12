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

#include "itkWrappedPhaseLaplacianImageFilter.h"
#include "itkTestingMacros.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkLaplacianImageFilter.h"
#include "itkWrapPhaseImageFilter.h"

int itkWrappedPhaseLaplacianImageFilterTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  
  //////////////
  // Typedefs //
  //////////////
  
  const unsigned int Dimension = 2;

  typedef double                                             PixelType;
  typedef itk::Image< PixelType, Dimension >                 ImageType;
  typedef itk::ImageRegionIteratorWithIndex< ImageType >     ItType;
  typedef itk::WrapPhaseImageFilter< ImageType >             WrapType;
  typedef itk::LaplacianImageFilter< ImageType, ImageType >  LaplacianType;
  typedef itk::WrappedPhaseLaplacianImageFilter< ImageType > WrappedLaplacianType;
  
  ////////////////
  // Test Image //
  ////////////////

  // Ramp image
  ImageType::Pointer input = ImageType::New();

  const ImageType::RegionType region({0,0},{10,10});
  input->SetRegions( region );
  input->Allocate();
  input->FillBuffer(0);

  ItType it(input, input->GetLargestPossibleRegion());
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
    it.Set(pow(it.GetIndex()[0]/2.0,2)); // Ramp 0 to 5, wrapped

  // Wrapped version
  WrapType::Pointer wrap = WrapType::New();
  wrap->SetInput( input );
  wrap->Update();
  ImageType::Pointer wrapped = wrap->GetOutput();

  ////////////////////////////////////
  // Wrapped Laplacian vs Laplacian //
  ////////////////////////////////////

  LaplacianType::Pointer laplacian = LaplacianType::New();
  laplacian->SetInput( input );
  laplacian->Update();

  WrappedLaplacianType::Pointer wrappedLaplacian = WrappedLaplacianType::New();
  wrappedLaplacian->SetInput( wrapped );
  wrappedLaplacian->Update();

  ItType lIt(laplacian->GetOutput(),
             laplacian->GetOutput()->GetLargestPossibleRegion());
  ItType wIt(wrappedLaplacian->GetOutput(),
             wrappedLaplacian->GetOutput()->GetLargestPossibleRegion());

  unsigned int incorrect = 0;
  for (lIt.GoToBegin(), wIt.GoToBegin(); !lIt.IsAtEnd(); ++lIt, ++wIt)
    {
    if (std::abs(lIt.Get() - wIt.Get()) > 10e-6)
      {
      ++incorrect;
      std::cerr << "ERROR: Difference found between normal and wrapped." << std::endl;
      std::cerr << "Normal: " << lIt.Get() << std::endl;
      std::cerr << "Wrapped: " << wIt.Get() << std::endl;
      }
    }

  if (0 < incorrect)
    {
    std::cerr << "ERROR: " << incorrect << " misses were detected." << std::endl;
    return EXIT_FAILURE;
    }

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( wrappedLaplacian, WrappedLaplacianType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  TEST_SET_GET_VALUE( false, wrappedLaplacian->GetWeighted() );
  wrappedLaplacian->SetWeighted( true );
  TEST_SET_GET_VALUE( true, wrappedLaplacian->GetWeighted() );  

  return EXIT_SUCCESS;

}
