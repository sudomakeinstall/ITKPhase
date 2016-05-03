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
#ifndef itkWrapPhasePositiveFunctor_h
#define itkWrapPhasePositiveFunctor_h

#include <vnl/vnl_math.h>

namespace itk
{
namespace Functor
{
/** \class WrapPhasePositiveFunctor
 *  \ingroup ITKPhase
 *  \brief Unary functor that wraps the input value into the range [0 to 2pi).
 *
 * This functor is used by WrapPhasePositiveImageFilter as well as filters that inherit
 * from PhaseImageToImageFilter.  The input value is cast to double, wrapped, and then
 * cast to the output pixel type.
 *
 */


template< typename TInputPixel, typename TOutputPixel = TInputPixel >
class WrapPhasePositiveFunctor
{
public:
  WrapPhasePositiveFunctor() {}
  ~WrapPhasePositiveFunctor() {}
  
  bool operator!=(const WrapPhasePositiveFunctor &) const
  {
    return false;
  }

  bool operator==(const WrapPhasePositiveFunctor & other) const
  {
    return !( *this != other );
  }

  inline TOutputPixel operator()(const TInputPixel & pix) const
  {
    return static_cast<TOutputPixel>(vnl_math::angle_0_to_2pi(static_cast<double>(pix)));
  }
  
};


}  // end namespace functor
}  // end namespace itk

#endif
