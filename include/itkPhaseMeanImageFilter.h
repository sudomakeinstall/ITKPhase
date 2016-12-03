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
#ifndef itkPhaseMeanImageFilter_h
#define itkPhaseMeanImageFilter_h
 
#include "itkPhaseImageToImageFilter.h"
#include "itkObjectFactory.h"
#include "itkSinImageFilter.h"
#include "itkCosImageFilter.h"
#include "itkIntegralImageFilter.h"
#include "itkAtan2ImageFilter.h"
#include "itkMeanFromIntegralImageFilter.h"

namespace itk
{
/** \class PhaseMeanImageFilter
 * \brief Calculates the average wrappedphase in an nxn neighborhood.
 *
 * This filter assumes a phase image wrapped into the range of -pi to pi as input and
 * calculates the average phase in an nxn neighborhood.
 *
 * In general, the signal from which the phase was extracted should be filtered rather
 * than the phase itself.  However, in cases where the original data is not available
 * (for example, the only the phase data from an MRI acquisition was reconstructed on
 * the scanner, and the complete complex data has been discarded), it may be necessary
 * to filter the phase data itself.  However, treating phase as a typical scalar will
 * yield incorrect results.  For example, the average of two phase pixels is not
 * (pixel1 + pixel2) / 2, but rather atan2(sin(pixel1) + sin(pixel2), cos(pixel1) + cos(pixel2).
 * Therefore, it is necessary to define ITK filters to accomplish these tasks.
 *
 * Please see  "2D Phase Unwrapping: Theory, Algorithms, and Software" by Dennis C Ghiglia
 * and Mark D. Pritt for an excellent introduction to phase unwrapping.
 *
 * \ingroup ITKPhase
 */
template< typename TInputImage, typename TOutputImage = TInputImage >
class PhaseMeanImageFilter:
public PhaseImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef PhaseMeanImageFilter                                 Self;
  typedef PhaseImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                                 Pointer;
  typedef SmartPointer< const Self >                           ConstPointer;
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(PhaseMeanImageFilter, PhaseImageToImageFilter);

  /** n-dimensional Kernel radius. */
  typedef typename TInputImage::SizeType RadiusType;

  /** Set the index of a pixel with high phase quality. */
  itkSetMacro( Radius, RadiusType );

  /** Get the index of a pixel with high phase quality. */
  itkGetMacro( Radius, RadiusType );

protected:

  PhaseMeanImageFilter();
  ~PhaseMeanImageFilter(){}

  typedef SinImageFilter<              TInputImage, TOutputImage >                SinType;
  typedef CosImageFilter<              TInputImage, TOutputImage >                CosType;
  typedef Atan2ImageFilter<            TOutputImage, TOutputImage, TOutputImage > Atan2Type;
  typedef IntegralImageFilter<         TOutputImage, TOutputImage >               IntegralType;
  typedef MeanFromIntegralImageFilter< TOutputImage, TOutputImage >               MeanType;

  void GenerateData() ITK_OVERRIDE;
 
private:

  ITK_DISALLOW_COPY_AND_ASSIGN(PhaseMeanImageFilter);

  // User input
  RadiusType m_Radius;

  // Filters
  typename SinType::Pointer      m_Sin;
  typename CosType::Pointer      m_Cos;
  typename IntegralType::Pointer m_Sin_Int;
  typename IntegralType::Pointer m_Cos_Int;
  typename MeanType::Pointer     m_MeanSin;
  typename MeanType::Pointer     m_MeanCos;
  typename Atan2Type::Pointer    m_Atan2;

};
} //namespace ITK
 
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPhaseMeanImageFilter.hxx"
#endif

#endif
