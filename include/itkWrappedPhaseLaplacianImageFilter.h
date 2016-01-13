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

#ifndef itkWrappedPhaseLaplacianImageFilter_h
#define itkWrappedPhaseLaplacianImageFilter_h

#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkConstNeighborhoodIterator.h"

#include "itkWrappedPhaseDifferencesBaseImageFilter.h"
#include "itkPhaseQualityImageFilter.h"

namespace itk
{
/** \class WrappedPhaseLaplacianImageFilter
 *  \ingroup ITKPhase
 * \brief the Laplacian for a wrapped phase image.
 *
 * The wrapped phase laplacian at a particular pixel is the sum over all dimensions of
 * the difference between the wrapped phase difference at that pixel and the wrapped
 * phase difference at the previous pixel (equation 5.32, [1]).
 *
 * Please see  [1] "2D Phase Unwrapping: Theory, Algorithms, and Software" by Dennis C Ghiglia
 * and Mark D. Pritt for an excellent introduction to phase unwrapping and phase residues.
 */
template< typename TInputImage, typename TOutputImage = TInputImage >
class WrappedPhaseLaplacianImageFilter:
public WrappedPhaseDifferencesBaseImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef WrappedPhaseLaplacianImageFilter                                    Self;
  typedef WrappedPhaseDifferencesBaseImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                                                Pointer;
  typedef SmartPointer< const Self >                                          ConstPointer;
  
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
  itkTypeMacro(WrappedPhaseLaplacianImageFilter, WrappedPhaseDifferencesBaseImageFilter);
  
  // Class Methods
  itkSetMacro(Weighted, bool);
  itkGetConstMacro(Weighted, bool);
  
  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const;
 
protected:

  WrappedPhaseLaplacianImageFilter();
  ~WrappedPhaseLaplacianImageFilter(){}
 
  /** Does the real work. */
  virtual void GenerateData();

private:

  WrappedPhaseLaplacianImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented
  
  typedef ConstNeighborhoodIterator< TInputImage > CNItType;
  typedef ImageRegionIterator< TInputImage >       ItType;
  typedef PhaseQualityImageFilter< TInputImage >   QualType;
 
  typename QualType::Pointer m_Qual = ITK_NULLPTR;
 
  bool m_Weighted;
 
};
} //namespace ITK
 
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkWrappedPhaseLaplacianImageFilter.hxx"
#endif
 
#endif
