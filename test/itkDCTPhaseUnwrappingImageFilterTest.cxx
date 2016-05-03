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
#include "itkNeighborhoodIterator.h"
#include "itkWrapPhaseSymmetricFunctor.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkTestingComparisonImageFilter.h"

int itkDCTPhaseUnwrappingImageFilterTest(int argc, char *argv[])
{
  
  if (argc != 3)
    {
    std::cerr << "Usage: " << argv[0] << " <wrapped_image> <unwrapped_image>" << std::endl;
    return EXIT_FAILURE;
    }

  //////////////
  // Typedefs //
  //////////////
  
  const unsigned int Dimension = 2;
  typedef double                                                      PixelType;
  typedef itk::Image< PixelType, Dimension >                          ImageType;
  typedef itk::DCTPhaseUnwrappingImageFilter< ImageType >             UnwrapType;
  typedef itk::ImageRegionIteratorWithIndex< ImageType >              ItType;
  typedef itk::NeighborhoodIterator< ImageType >                      NItType;
  typedef itk::Functor::WrapPhaseSymmetricFunctor< PixelType >        WrapType;
  typedef itk::ImageFileReader< ImageType >                           ReaderType;
  typedef itk::Testing::ComparisonImageFilter< ImageType, ImageType > DifferenceType;

  ////////////////////
  // Test Toy Image //
  ////////////////////

    {
    ImageType::Pointer wrapped = ImageType::New();
    WrapType wrap;
  
    const ImageType::IndexType index = {{0,0}};
    const ImageType::SizeType size = {{10,10}};
    const ImageType::RegionType region(index,size);
    wrapped->SetRegions( region );
    wrapped->Allocate();
    wrapped->FillBuffer(0);
  
    ItType it(wrapped, wrapped->GetLargestPossibleRegion());
    for (it.GoToBegin(); !it.IsAtEnd(); ++it)
      it.Set(wrap(it.GetIndex()[0]/2.0)); // Ramp 0 to 5, wrapped
  
    /////////////////
    // Test Filter //
    /////////////////
  
    UnwrapType::Pointer unwrap = UnwrapType::New();
    unwrap->SetInput( wrapped );
    unwrap->Update();
  
    ///////////////////////////////////
    // Make sure there are no wraps. //
    ///////////////////////////////////
  
    ImageType::IndexType itIndex = {{0,0}};
    ImageType::SizeType itSize = {{9,9}};
    ImageType::RegionType itRegion(itIndex,itSize);
    ImageType::SizeType itRadius = {{3,3}};
  
    NItType uit(itRadius, unwrap->GetOutput(), itRegion);
    unsigned int num_wraps = 0;
    for (uit.GoToBegin(); !uit.IsAtEnd(); ++uit)
      {
      PixelType c = uit.GetCenterPixel();
      PixelType x = uit.GetPixel(uit.GetStride(0));
      PixelType y = uit.GetPixel(uit.GetStride(1));
      if (std::fabs(c-x) < vnl_math::pi && std::fabs(c - y) < vnl_math::pi) continue;
      ++num_wraps;
      }
  
    if (0 < num_wraps)
      {
      std::cerr << "ERROR: " << num_wraps << " wraps were found." << std::endl;
      return EXIT_FAILURE;
      }
  
    // TODO: Should the gradient be the same in this case?  If so, add a test.

    ////////////
    // Basics //
    ////////////
  
    EXERCISE_BASIC_OBJECT_METHODS( unwrap,
                                   DCTPhaseUnwrappingImageFilter,
                                   PhaseImageToImageFilter );

    }

  ////////////////////
  // Test SWI Image //
  ////////////////////

  ReaderType::Pointer wrappedReader = ReaderType::New();
  ReaderType::Pointer unwrappedReader = ReaderType::New();

  wrappedReader->SetFileName( argv[1] );
  unwrappedReader->SetFileName( argv[2] );

  UnwrapType::Pointer unwrap = UnwrapType::New();
  unwrap->SetInput( wrappedReader->GetOutput() );

  DifferenceType::Pointer diff = DifferenceType::New();
  diff->SetValidInput( unwrappedReader->GetOutput() );
  diff->SetTestInput( unwrap->GetOutput() );
  diff->Update();

  std::cout << "TOTAL DIFFERENCE: " << diff->GetTotalDifference() << std::endl;
  
  return EXIT_SUCCESS;

}
