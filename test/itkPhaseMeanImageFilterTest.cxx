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
#include "itkTestingMacros.h"

#include "itkPhaseMeanImageFilter.h"

int
itkPhaseMeanImageFilterTest(int itkNotUsed(argc), char* itkNotUsed(argv)[])
{
  typedef itk::Image< double, 2> TImage;
  typedef itk::PhaseMeanImageFilter< TImage > TPhaseMean;

  TPhaseMean::Pointer mean = TPhaseMean::New();

  return EXIT_SUCCESS;
}
