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

#ifndef itkHelmholtzDecompositionImageFilter_h
#define itkHelmholtzDecompositionImageFilter_h

/** ITK headers */
#include "itkObjectFactory.h"
#include "itkSubtractImageFilter.h"

/** Custom headers */
#include "itkPhaseImageToImageFilter.h"
#include "itkDCTPhaseUnwrappingImageFilter.h"
#include "itkWrapPhaseSymmetricImageFilter.h"

namespace itk {

/** \class HelmholtzDecompositionImageFilter
 *  \ingroup ITKPhase
 *  \brief Decomposes a wrapped phase image into its rotational (curl) and irrotational
 * (divergence) components.
 *
 * This filter assumes a phase image wrapped into the range [-pi to pi) as input
 * and provides the rotational and irrotational components of the phase as outputs,
 * through the GetRotational() and GetIrrotational() methods, respectively.
 *
 */

template< typename TInputImage, typename TOutputImage = TInputImage >
class HelmholtzDecompositionImageFilter:
public PhaseImageToImageFilter< TInputImage, TOutputImage >
{
public:

  /** Standard class typedefs. */
  typedef HelmholtzDecompositionImageFilter                    Self;
  typedef PhaseImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                                 Pointer;
  typedef SmartPointer< const Self >                           ConstPointer;
  
  #ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( SameDimensionCheck,
                   ( Concept::SameDimension< TInputImage::ImageDimension, TOutputImage::ImageDimension > ) );
  
  itkConceptMacro( InputFloatingPointCheck,
                   ( Concept::IsFloatingPoint< typename TInputImage::PixelType > ) );
                   
  itkConceptMacro( OutputFloatingPointCheck,
                   ( Concept::IsFloatingPoint< typename TOutputImage::PixelType > ) );
  // End concept checking
  #endif
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(HelmholtzDecompositionImageFilter, PhaseImageToImageFilter);

  /** Use this to retrieve the phase quality map. */
  TOutputImage* GetIrrotational();

  /** Use this to retrieve the unwrapped phase. */
  TOutputImage* GetRotational();
  
  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const ITK_OVERRIDE;
 
protected:

  HelmholtzDecompositionImageFilter();
  ~HelmholtzDecompositionImageFilter(){}

  /** Does the real work. */
  virtual void GenerateData() ITK_OVERRIDE;

  /** Declare component filter types */
  typedef DCTPhaseUnwrappingImageFilter< TInputImage > UnwrapType;
  typedef SubtractImageFilter< TInputImage >           SubtractType;
  typedef WrapPhaseSymmetricImageFilter< TInputImage > WrapType;

  /** Used to create the output images when the GetOutput(n) method is called. */
  DataObject::Pointer MakeOutput(long unsigned int idx); 
 
private:

  ITK_DISALLOW_COPY_AND_ASSIGN(HelmholtzDecompositionImageFilter);
  
  /** Instantiate component filters */
  typename UnwrapType::Pointer   m_Unwrap;
  typename SubtractType::Pointer m_Subtract;
  typename WrapType::Pointer     m_WrapIrrot;
  typename WrapType::Pointer     m_WrapRot;
 
};

} //namespace ITK

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkHelmholtzDecompositionImageFilter.hxx"
#endif
 
#endif
