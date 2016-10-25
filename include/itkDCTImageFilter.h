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

#ifndef itkDCTImageFilter_h 
#define itkDCTImageFilter_h 

#include "itkFFTWGlobalConfiguration.h"
#ifndef ITK_USE_FFTWD
#error "itkDCTImageFilter.h is dependent upon the double precision fftw library.  In order to use this filter, please rebuild itk, setting the cmake variable ITK_USE_FFTWD to ON."
#endif

#include "itkImage.h" // Common
#include "itkImageToImageFilter.h" // Common
#include "itkDivideImageFilter.h" // ImageIntensity 
#include "itkConceptChecking.h" // Common
#include <fftw3.h>

namespace itk {

/** \class DCTImageFilter
 *  \ingroup ITKPhase
 * \brief Calculates discrete cosine transform of an image.
 *
 * This class makes use of the FFTW library's real to real transform.
 * Please ensure that ITK was built with USE_FFTWD before using this class.
 * USE_FFTWD can be turned on as an advanced option during the CMake configuration
 * of the ITK library, prior to the build.
 *
 * Currently, the forward transform uses FFTW_REDFT10, and the reverse transform
 * uses FFTW_REDFT01.  In the future, the filter could be extended to allow for
 * FFTW_REDFT11 and FFTW_REDFT00, as well as odd transforms.  Note that these may
 * require different normalization procedures for the reverse transform.
 *
 * Note also that the licensing for FFTW differs from that of ITK.  Filters making
 * use of the FFTW library must conform to the General Public License (GPL).  Please
 * consult http://www.fftw.org/ for documentation of the DCT as well as for
 * further licensing information.
 *
 */

template < typename TInputImage, typename TOutputImage = TInputImage > 
class DCTImageFilter : 
public ImageToImageFilter< TInputImage, TOutputImage > 
{ 
public: 

  //  Standard declarations 
  typedef DCTImageFilter                                  Self; 
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass; 
  typedef SmartPointer<Self>                              Pointer; 
  typedef SmartPointer<const Self>                        ConstPointer; 

  // Transform DIRECTION
  typedef  enum { Forward=0, Reverse=1 } TransformDirectionEnumType;
  
#ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( SameDimensionCheck,
                   ( Concept::SameDimension< TInputImage::ImageDimension,
                   TOutputImage::ImageDimension > ) );
  
  itkConceptMacro( InputFloatingPointCheck,
                   ( Concept::IsFloatingPoint< typename TInputImage::PixelType > ) );
                   
  itkConceptMacro( OutputFloatingPointCheck,
                   ( Concept::IsFloatingPoint< typename TOutputImage::PixelType > ) );
  // End concept checking
#endif
  
  itkSetMacro(TransformDirection, TransformDirectionEnumType);
  itkGetConstMacro(TransformDirection, TransformDirectionEnumType);

  /** Method for creation through object factory */
  itkNewMacro(Self);

  /** Run-time type information */
  itkTypeMacro(DCTImageFilter, ImageToImageFilter);

  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const ITK_OVERRIDE;

protected: 

  DCTImageFilter();
  ~DCTImageFilter(){}

  // Transform DIRECTION
  TransformDirectionEnumType m_TransformDirection;

  //  Declare the component filter types:
  typedef DivideImageFilter< TInputImage, TInputImage, TInputImage > DivideType;
        
  void GenerateData() ITK_OVERRIDE;

private: 

  ITK_DISALLOW_COPY_AND_ASSIGN(DCTImageFilter);

//  Component filters are declared as data members, all using the smart 
//  pointer types.
  typename DivideType::Pointer m_Divide = ITK_NULLPTR;

}; 

}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkDCTImageFilter.hxx"
#endif

#endif
