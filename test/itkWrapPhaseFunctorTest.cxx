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

#include "itkWrapPhaseFunctor.h"
#include "itkNumericTraits.h"
#include "vnl/vnl_math.h"
#include <iostream>

bool different(double a, double b)
{
// TODO: Wrap functor uses a simplistic algorithm which results in numerical instability
// Differences are > epsilon from the numeric traits
// Consider the following alternate implementation:
// http://stackoverflow.com/questions/4633177/c-how-to-wrap-a-float-to-the-interval-pi-pi
// return std::fabs(a-b) > itk::NumericTraits< double >::epsilon();
return std::fabs(a-b) > 10e-6;
}

int itkWrapPhaseFunctorTest(int argc, char **argv)
{

  if (argc != 1)
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }

  itk::Functor::WrapPhaseFunctor< double > wrapFunc;
  
  if (different( wrapFunc( 3.0 ), 3.0) ) {
    std::cerr << "Incorrect wrapping of 3.0." << std::endl;
    return EXIT_FAILURE;
  }

  if (different(wrapFunc( 0.0 ), 0.0) ) {
    std::cerr << "Incorrect wrapping of 0.0." << std::endl;
    return EXIT_FAILURE;
  }

  if (different(wrapFunc( -3.0 ), -3.0 ) ) {
    std::cerr << "Incorrect wrapping of -3.0." << std::endl;
    return EXIT_FAILURE;
  }

  if (different(wrapFunc( 1.0 + vnl_math::pi ), (-vnl_math::pi + 1.0) ) ) {
    std::cerr << "Incorrect wrapping of 1.0 + pi." << std::endl;
    return EXIT_FAILURE;
  }

  if (different(wrapFunc( -vnl_math::pi - 1.0 ), (vnl_math::pi - 1.0 ) ) ) {
    std::cerr << "Incorrect wrapping of -pi - 1.0." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;

}
