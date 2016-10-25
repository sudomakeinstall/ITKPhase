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

#ifndef itkPhaseExamplesImageSource_h
#define itkPhaseExamplesImageSource_h

/** ITK headers */
#include "itkImageSource.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkPasteImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkAdditiveGaussianNoiseImageFilter.h"
#include "itkWrapPhaseSymmetricImageFilter.h"
#include "vnl/vnl_math.h"

namespace itk {

/** \class PhaseExamplesImageSource
 *  \ingroup ITKPhase
 * \brief Provides a variety of simulated phase images for demonstrating and testing
 * phase filters.
 *
 * Currently, this filter provides a phase ramp, which can be optionally modified with
 * a line of shear and a patch of noise.
 *
 */

template< typename TImage >
class PhaseExamplesImageSource:
public ImageSource< TImage >
{
public:

  /** Standard class typedefs. */
  typedef PhaseExamplesImageSource   Self;
  typedef ImageSource< TImage >      Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(PhaseExamplesImageSource, ImageSource);
  
  // Class Methods
  itkSetMacro(Shear, bool);
  itkGetConstMacro(Shear, bool);
  
  itkSetMacro(Noise, bool);
  itkGetConstMacro(Noise, bool);
  
  itkSetMacro(NoiseSD, double);
  itkGetConstMacro(NoiseSD, double);
  
  itkSetMacro(NoiseMean, double);
  itkGetConstMacro(NoiseMean, double);
  
  itkSetMacro(NoiseSeed, unsigned int );
  itkGetConstMacro(NoiseSeed, unsigned int );
  
  itkSetMacro(Wrap, bool);
  itkGetConstMacro(Wrap, bool);
  
  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const ITK_OVERRIDE;

  void Reset();
 
protected:

  PhaseExamplesImageSource();
  ~PhaseExamplesImageSource(){}

  /** Does the real work. */
  void GenerateData() ITK_OVERRIDE;

private:

  ITK_DISALLOW_COPY_AND_ASSIGN(PhaseExamplesImageSource);
  
  /** Declare component filter types */
  typedef ImageRegionIteratorWithIndex< TImage >        ItType;
  typedef AdditiveGaussianNoiseImageFilter< TImage >    NoiseType;
  typedef RegionOfInterestImageFilter< TImage, TImage > ROIType;
  typedef PasteImageFilter< TImage >                    PasteType;
  typedef WrapPhaseSymmetricImageFilter< TImage >       WrapType;
 
  /** Instantiate component filters */
  typename NoiseType::Pointer m_NoiseFilter;
  typename ROIType::Pointer   m_ROIFilter;
  typename PasteType::Pointer m_PasteFilter;
  typename WrapType::Pointer  m_WrapFilter;
  
  bool         m_Shear;
  bool         m_Noise;
  bool         m_Wrap;
  double       m_NoiseSD;
  double       m_NoiseMean;
  unsigned int m_NoiseSeed;
 
};

} //namespace ITK

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPhaseExamplesImageSource.hxx"
#endif
 
#endif
