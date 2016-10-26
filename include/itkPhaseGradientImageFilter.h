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

#ifndef itkPhaseGradientImageFilter_h
#define itkPhaseGradientImageFilter_h
 
#include <itkObjectFactory.h>
#include <itkCovariantVector.h>
#include <itkGradientImageFilter.h>
#include <itkVectorMagnitudeImageFilter.h>
#include <itkAddImageFilter.h>
#include <itkWrapPhaseSymmetricImageFilter.h>
#include <itkLogicOpsFunctors.h>
#include <itkTernaryOperatorImageFilter.h>
#include <itkBinaryFunctorImageFilter.h>

namespace itk
{
/** \class PhaseGradientImageFilter
 *  \ingroup ITKPhase
 *  \brief This class calculates the (wrapped) phase gradient of the input image.
 *
 *  The 
 */
template< typename TInputImage, typename TOutputImage >
class PhaseGradientImageFilter:
public ImageToImageFilter< TInputImage, TOutputImage >
{
public:

  /** Standard class typedefs. */
  typedef PhaseGradientImageFilter                        Self;
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                            Pointer;
  typedef SmartPointer< const Self>                       ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(PhaseGradientImageFilter, ImageToImageFilter);
  
  #ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( SameDimensionCheck,
                   ( Concept::SameDimension< TInputImage::ImageDimension,
                                             TOutputImage::ImageDimension > ) );
  
  itkConceptMacro( InputFloatingPointCheck,
                   ( Concept::IsFloatingPoint< typename TInputImage::PixelType > ) );
  // End concept checking
  #endif

  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const ITK_OVERRIDE;
 
protected:

  PhaseGradientImageFilter();
  ~PhaseGradientImageFilter(){}

  typedef Image< bool, TInputImage::ImageDimension > TLogicalImage;
  typedef typename TInputImage::PixelType            TInputPixel;

  typedef GradientImageFilter< TInputImage,
                               TInputPixel,
                               TInputPixel,
                               TOutputImage >                     TGradient;

  typedef VectorMagnitudeImageFilter< TOutputImage, TInputImage > TMagnitude;
  typedef AddImageFilter< TInputImage >                           TAdd;
  typedef WrapPhaseSymmetricImageFilter< TInputImage >            TWrap;
  typedef Functor::Less< TInputPixel, TInputPixel, bool >         TLessFunctor;

  typedef BinaryFunctorImageFilter< TInputImage,
                                    TInputImage,
                                    TLogicalImage,
                                    TLessFunctor > TMinMask;

  typedef TernaryOperatorImageFilter< TLogicalImage, TOutputImage > TChoose;

  void GenerateData() ITK_OVERRIDE;
 
private:

  ITK_DISALLOW_COPY_AND_ASSIGN(PhaseGradientImageFilter);
  
};

} //namespace ITK

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPhaseGradientImageFilter.hxx"
#endif
 
#endif
