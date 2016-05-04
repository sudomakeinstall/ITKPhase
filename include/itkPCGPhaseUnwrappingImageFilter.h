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
#ifndef itkPCGPhaseUnwrappingImageFilter_h
#define itkPCGPhaseUnwrappingImageFilter_h
 
#include "itkPhaseImageToImageFilter.h"
#include "itkObjectFactory.h"
#include "itkWrappedPhaseLaplacianImageFilter.h"
#include "itkDCTPhaseUnwrappingImageFilter.h"
#include "itkNeighborhoodIterator.h"
#include "itkImageRegionIterator.h"

namespace itk
{
/** \class PCGPhaseUnwrappingImageFilter
 * \ingroup ITKPhase
 * \brief Calculates weighted least squares phase unwrapping solution.
 *
 * Please see  "2D Phase Unwrapping: Theory, Algorithms, and Software" by Dennis C Ghiglia
 * and Mark D. Pritt for an excellent introduction to phase unwrapping and phase residues.
 */
template< class TImage>
class PCGPhaseUnwrappingImageFilter:public PhaseImageToImageFilter< TImage, TImage >
{
public:
  /** Standard class typedefs. */
  typedef PCGPhaseUnwrappingImageFilter             Self;
  typedef PhaseImageToImageFilter< TImage, TImage > Superclass;
  typedef SmartPointer< Self >                      Pointer;
  typedef SmartPointer< const Self >                ConstPointer;
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(PCGPhaseUnwrappingImageFilter, PhaseImageToImageFilter);
  
  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const ITK_OVERRIDE;

  itkSetMacro( MaximumIterations, unsigned int );
  itkGetConstMacro( MaximumIterations, unsigned int ); 

  itkSetMacro( MinimumEpsilon, unsigned int );
  itkGetConstMacro( MinimumEpsilon, unsigned int ); 

 
protected:

  PCGPhaseUnwrappingImageFilter();
  ~PCGPhaseUnwrappingImageFilter(){}
  
  // Component filters
  typedef WrappedPhaseLaplacianImageFilter< TImage, TImage > LaplacianType;
  typedef PhaseDerivativeVarianceImageFilter< TImage >       QualType;
  typedef DCTPhaseUnwrappingImageFilter< TImage >            DCTType;

  typedef NeighborhoodIterator< TImage >                     NItType;
  typedef ImageRegionIterator< TImage >                      ItType;

  /** Does the real work. */
  void GenerateData() ITK_OVERRIDE;
 
private:

  PCGPhaseUnwrappingImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented
  
  typename LaplacianType::Pointer m_Laplacian;
  typename QualType::Pointer      m_Qual;
  typename DCTType::Pointer       m_DCT;

  unsigned int m_MaximumIterations;
  double       m_MinimumEpsilon;

};
} //namespace ITK
 
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPCGPhaseUnwrappingImageFilter.hxx"
#endif
 
#endif
