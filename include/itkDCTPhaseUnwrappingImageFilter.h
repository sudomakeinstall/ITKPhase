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
#ifndef __itkDCTPhaseUnwrappingImageFilter_h
#define __itkDCTPhaseUnwrappingImageFilter_h

#include "itkPhaseImageToImageFilter.h"
#include "itkWrappedPhaseLaplacianImageFilter.h"
#include "itkStatisticsImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkDCTPoissonSolverImageFilter.h"

namespace itk {

/** \class DCTPhaseUnwrappingImageFilter
 * \brief Calculates calculates the L2-norm unwrapped phase.
 *
 * This filter uses the discrete cosine transform to calculate the L2-norm
 * unwrapped phase.  The DCT is computed using the FFTW library.  There are no restrictions
 * on the dimensions of the input image.  The filter assumes a phase image wrapped into
 * the range of -pi to pi.  Output is not congruent with the input phase.
 *
 */

template < typename TInputImage, typename TOutputImage = TInputImage >
class DCTPhaseUnwrappingImageFilter:
public PhaseImageToImageFilter< TInputImage, TOutputImage >
{
public:

//  Standard declarations
//  Used for object creation with the object factory:

  typedef DCTPhaseUnwrappingImageFilter                        Self;
  typedef PhaseImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer<Self>                                   Pointer;
  typedef SmartPointer<const Self>                             ConstPointer;
  
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
  
  /** Method for creation through object factory */
  itkNewMacro(Self);
  	
  /** Run-time type information */
  itkTypeMacro(DCTPhaseUnwrappingImageFilter, PhaseImageToImageFilter);

  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const;

protected:

  DCTPhaseUnwrappingImageFilter();
  ~DCTPhaseUnwrappingImageFilter(){}
  
  void GenerateData();

private:

  DCTPhaseUnwrappingImageFilter(Self&); // intentionally not implemented
  void operator=(const Self&); // intentionally not implemented
  
  // Component filter types
  typedef itk::WrappedPhaseLaplacianImageFilter< TInputImage > PType;
  typedef itk::StatisticsImageFilter< TInputImage >            StatsType;
  typedef itk::SubtractImageFilter< TInputImage >              SubtractType;
  typedef itk::DCTPoissonSolverImageFilter< TInputImage >      SolverType;

  typename PType::Pointer        m_P;
  typename StatsType::Pointer    m_Stats;
  typename SubtractType::Pointer m_Subtract;
  typename SolverType::Pointer   m_Solver;
  
};

}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkDCTPhaseUnwrappingImageFilter.txx"
#endif

#endif // __itkDCTPhaseUnwrappingImageFilter_h
