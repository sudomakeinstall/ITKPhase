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
#ifndef itkTernaryOperatorImageFilter_h
#define itkTernaryOperatorImageFilter_h

#include "itkTernaryFunctorImageFilter.h"

namespace itk
{
namespace Functor
{
/**
 * \class TernaryOperator
 * \brief
 * \ingroup ITKPhase
 */
template< typename TInput1, typename TInput2, typename TInput3, typename TOutput >
class TernaryOperator
{
public:
  TernaryOperator() {}
  ~TernaryOperator() {}
  bool operator!=(const TernaryOperator &) const
  {
    return false;
  }

  bool operator==(const TernaryOperator & other) const
  {
    return !( *this != other );
  }

  inline TOutput operator()(const TInput1 & A,
                            const TInput2 & B,
                            const TInput3 & C) const
  { return (TOutput)( A ? B : C ); }
};
}
/** \class TernaryOperatorImageFilter
 * \brief Apply the ternary operator pixelwise across three images.
 *
 * This class is templated over the types of the three
 * input images and the type of the output image.
 * If the value of Input1 evaluates to true, the value of Input2 is taken.
 * Otherwise, the value of Input3 is taken:
 *
 * Input1 ? Input2 : Input3
 *
 * Numeric conversions (castings) are done by the C++ defaults.
 *
 * \ingroup ITKPhase
 */
template< typename TInputImage1, typename TInputImage2,
          typename TInputImage3, typename TOutputImage >
class TernaryOperatorImageFilter:
  public
  TernaryFunctorImageFilter< TInputImage1, TInputImage2,
                             TInputImage3, TOutputImage,
                             Functor::TernaryOperator< typename TInputImage1::PixelType,
                                            typename TInputImage2::PixelType,
                                            typename TInputImage3::PixelType,
                                            typename TOutputImage::PixelType >   >
{
public:
  /** Standard class typedefs. */
  typedef TernaryOperatorImageFilter Self;
  typedef TernaryFunctorImageFilter<
    TInputImage1, TInputImage2,
    TInputImage3, TOutputImage,
    Functor::TernaryOperator< typename TInputImage1::PixelType,
                              typename TInputImage2::PixelType,
                              typename TInputImage3::PixelType,
                              typename TOutputImage::PixelType > > Superclass;

  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(TernaryOperatorImageFilter,
               TernaryFunctorImageFilter);

protected:
  TernaryOperatorImageFilter() {}
  virtual ~TernaryOperatorImageFilter() {}

private:
  TernaryOperatorImageFilter(const Self &) ITK_DELETE_FUNCTION;
  void operator=(const Self &) ITK_DELETE_FUNCTION;
};
} // end namespace itk

#endif
