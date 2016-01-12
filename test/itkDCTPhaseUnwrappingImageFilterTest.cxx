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

#include "itkDCTPhaseUnwrappingImageFilter.h"
#include "itkTestingMacros.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkWrapPhaseFunctor.h"

int itkDCTPhaseUnwrappingImageFilterTest(int argc, char **argv)
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
  typedef double                                          PixelType;
  typedef itk::Image< PixelType, Dimension >              ImageType;
  typedef itk::DCTPhaseUnwrappingImageFilter< ImageType > UnwrapType;
  typedef itk::ImageRegionIteratorWithIndex< ImageType >  ItType;
  typedef itk::Functor::WrapPhaseFunctor< PixelType >     WrapType;

  ////////////////
  // Test Image //
  ////////////////

  ImageType::Pointer wrapped = ImageType::New();
  WrapType wrap;

  const ImageType::RegionType region({0,0},{10,10});
  wrapped->SetRegions( region );
  wrapped->Allocate();
  wrapped->FillBuffer(0);

  ItType it(wrapped, wrapped->GetLargestPossibleRegion());
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
    {
    it.Set(wrap(it.GetIndex()[0]/2.0)); // Ramp 0 to 5, wrapped
    std::cout << it.Get() << std::endl;
    }

  /////////////////
  // Test Filter //
  /////////////////

  UnwrapType::Pointer unwrap = UnwrapType::New();
  unwrap->SetInput( wrapped );
  unwrap->Update();

  ItType fit(unwrap->GetOutput(), unwrap->GetOutput()->GetLargestPossibleRegion());
  for (fit.GoToBegin(); !fit.IsAtEnd(); ++fit)
    {
    std::cout << fit.Get() << std::endl;
    }

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( unwrap, UnwrapType ); 
  
  return EXIT_SUCCESS;

}
