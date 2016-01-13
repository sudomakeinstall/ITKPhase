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

#include "itkDCTImageFilter.h"
#include "itkTestingMacros.h"
#include "itkImageRegionIteratorWithIndex.h"

static bool different(double a, double b)
{
  return std::fabs(a-b) > 10e-6;
}

static bool same(double a, double b)
{
  return !different(a, b);
}

int itkDCTImageFilterTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }

  ////////////////////////////////////////////////
  // Setup I/O to output with higher precision. //
  ////////////////////////////////////////////////

  std::cout.precision(8);
  std::cerr.precision(8);

  //////////////
  // Typedefs //
  //////////////
  
  const unsigned int Dimension = 2;

  typedef double                                         PixelType;
  typedef itk::Image< PixelType, Dimension >             ImageType;
  typedef itk::DCTImageFilter< ImageType >               FilterType;
  typedef itk::ImageRegionIteratorWithIndex< ImageType > ItType;

  /////////////
  // Filters //
  /////////////

  FilterType::Pointer forward = FilterType::New();
  FilterType::Pointer inverse = FilterType::New();

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( forward, FilterType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  TEST_SET_GET_VALUE( FilterType::Forward, forward->GetTransformDirection() );
  forward->SetTransformDirection( FilterType::Reverse );
  TEST_SET_GET_VALUE( FilterType::Reverse, forward->GetTransformDirection() );  

  ////////////////
  // Test Image //
  ////////////////

  ImageType::Pointer constant = ImageType::New();

  const ImageType::IndexType index = {{0,0}};
  const ImageType::SizeType size = {{3,4}};
  const ImageType::RegionType region(index,size);
  constant->SetRegions( region );
  constant->Allocate();
  constant->FillBuffer(5);

  //////////////////////////////////////////////
  // Run the filter in the forward direction. //
  //////////////////////////////////////////////

  forward->SetInput( constant );
  forward->SetTransformDirection( FilterType::Forward );
  forward->Update();

  // The sum of the logical array should be in the DC component (0,0)
  // Since the DCT is reflected, the logical array is twice the size
  // of the actual array in each dimension.

  const ImageType::IndexType zeroIndex = {{0,0}};
  const PixelType dc_measured = forward->GetOutput()->GetPixel(zeroIndex);
  const PixelType dc_predicted = (3*2)*(4*2)*5;
  if (different(dc_measured,dc_predicted))
    {
    std::cerr << "ERROR: DC component is incorrect." << std::endl;
    std::cerr << "Measured: " << dc_measured << std::endl;
    std::cerr << "Predicted: " << dc_predicted << std::endl;
    return EXIT_FAILURE;
    }

  // Since the image was constant, the remaining pixels should be zero.

  ItType fit(forward->GetOutput(), forward->GetOutput()->GetLargestPossibleRegion());
  for (fit.GoToBegin(); !fit.IsAtEnd(); ++fit)
    {
    if (0 == fit.GetIndex()[0] + fit.GetIndex()[1]) continue;
    if (same(fit.Get(),0.)) continue;
    std::cerr << "ERROR: The value should be near zero." << std::endl;
    std::cerr << "Value: " << std::fixed << fit.Get() << std::endl;
    std::cerr << "Index: " << fit.GetIndex() << std::endl;
    return EXIT_FAILURE;
    }

  //////////////////////////////////////////////
  // Run the filter in the inverse direction. //
  //////////////////////////////////////////////

  inverse->SetTransformDirection( FilterType::Reverse );
  inverse->SetInput( forward->GetOutput() );
  inverse->Update();

  ItType rit(inverse->GetOutput(), inverse->GetOutput()->GetLargestPossibleRegion());
  ItType iit(constant, inverse->GetOutput()->GetLargestPossibleRegion());

  for (rit.GoToBegin(), iit.GoToBegin(); !rit.IsAtEnd(); ++rit, ++iit)
    {
    if (same(rit.Get(),iit.Get())) continue;
    std::cerr << "ERROR: The input and output pixels are not the same." << std::endl;
    std::cerr << "Input: " << iit.Get() << std::endl;
    std::cerr << "Output: " << rit.Get() << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;

}
