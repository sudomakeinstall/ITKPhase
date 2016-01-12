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

#include "itkDCTPoissonSolverImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkLaplacianImageFilter.h"
#include "itkTestingMacros.h"

int itkDCTPoissonSolverImageFilterTest(int argc, char **argv)
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

  typedef double                                            PixelType;
  typedef itk::Image< PixelType, Dimension >                ImageType;
  typedef itk::ImageRegionIteratorWithIndex< ImageType >    ItType;
  typedef itk::LaplacianImageFilter< ImageType, ImageType > LaplacianType;
  typedef itk::DCTPoissonSolverImageFilter< ImageType >     SolverType;

  LaplacianType::Pointer laplacian = LaplacianType::New();
  SolverType::Pointer solver = SolverType::New();

  ////////////////
  // Test Image //
  ////////////////

  ImageType::Pointer input = ImageType::New();

  const ImageType::RegionType region({0,0},{10,10});
  input->SetRegions( region );
  input->Allocate();
  input->FillBuffer(0);

  ItType inIt(input, input->GetLargestPossibleRegion());
  for (inIt.GoToBegin(); !inIt.IsAtEnd(); ++inIt)
    inIt.Set(pow(inIt.GetIndex()[1]-5,2));

  //////////////
  // Pipeline //
  //////////////

  laplacian->SetInput( input );
  solver->SetInput( laplacian->GetOutput() );
  solver->Update();

  ItType inpIt(input, input->GetLargestPossibleRegion());
  ItType lapIt(laplacian->GetOutput(), laplacian->GetOutput()->GetLargestPossibleRegion());
  ItType outIt(solver->GetOutput(), solver->GetOutput()->GetLargestPossibleRegion());

  for (inpIt.GoToBegin(), lapIt.GoToBegin(), outIt.GoToBegin();
       !inpIt.IsAtEnd();
       ++inpIt, ++lapIt, ++outIt)
    {
    std::cout << inpIt.Get() << std::endl;
    std::cout << lapIt.Get() << std::endl;
    std::cout << outIt.Get() << std::endl << std::endl;
    }

  ////////////
  // Basics //
  ////////////

  EXERCISE_BASIC_OBJECT_METHODS( solver, SolverType ); 

  /////////////////////
  // Set/Get Methods //
  /////////////////////
  
  // No properties to set.

  return EXIT_SUCCESS;

}
