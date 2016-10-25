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

#ifndef itkItohPhaseUnwrappingImageFilter_h
#define itkItohPhaseUnwrappingImageFilter_h
 
#include "itkPhaseImageToImageFilter.h"
#include "itkObjectFactory.h"
#include "itkImageLinearIteratorWithIndex.h"
#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkImageAlgorithm.h"

namespace itk
{
/** \class ItohPhaseUnwrappingImageFilter
 *  \ingroup ITKPhase
 * \brief Unwraps a wrapped phase image using the Itoh algorithm.
 *
 * This filter assumes a phase image wrapped into the range of -pi to pi as input and
 * calculates unwrapped phase as output.  The Itoh algorithm unwraps phase linearly based
 * on adjacent phase values, passing through the image in the specified direction.
 *
 */
template< typename TInputImage, typename TOutputImage = TInputImage >
class ItohPhaseUnwrappingImageFilter:
public PhaseImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef ItohPhaseUnwrappingImageFilter                       Self;
  typedef PhaseImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                                 Pointer;
  typedef SmartPointer< const Self >                           ConstPointer;
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(ItohPhaseUnwrappingImageFilter, PhaseImageToImageFilter);
  
  /** Set the direction of the filter. */
  itkSetMacro( Direction, unsigned int );
  itkGetConstMacro( Direction, unsigned int );
  
  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const ITK_OVERRIDE;
 
protected:

  ItohPhaseUnwrappingImageFilter();
  ~ItohPhaseUnwrappingImageFilter(){}
 
  typedef ImageLinearConstIteratorWithIndex< TInputImage > InItType;
  typedef ImageLinearIteratorWithIndex< TOutputImage >     OutItType;

  unsigned int m_Direction;
 
  /** Does the real work. */
  virtual void GenerateData() ITK_OVERRIDE;
 
private:

  ITK_DISALLOW_COPY_AND_ASSIGN(ItohPhaseUnwrappingImageFilter);
 
};
} //namespace ITK
 
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkItohPhaseUnwrappingImageFilter.hxx"
#endif
 
#endif
