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
#ifndef __itkDCTPoissonSolverImageFilter_h
#define __itkDCTPoissonSolverImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkDCTImageFilter.h"

namespace itk {

/** \class DCTPoissonSolverImageFilter
 * \brief Solves the Poisson equation on a Laplacian image using the discrete cosine transform.
 *
 * The Laplacian (second-difference) image can be calculated using itkLaplacianImageFilter.h
 * This filter retrieves the original image (to an arbitrary constant) by solving the Poisson
 * equation using discrete cosine transform (DCT) methods.  The DCT is provided via the FFTW
 * library, and therefore is subject to the GPL license.  This can be useful for a variety of
 * image processing applications, such as phase unwrapping and gradient-domain filtering.
 *
 */

template < typename TInputImage, typename TOutputImage = TInputImage >
class DCTPoissonSolverImageFilter:
public ImageToImageFilter< TInputImage, TOutputImage >
{
public:

//  Standard declarations
//  Used for object creation with the object factory:

  typedef DCTPoissonSolverImageFilter                      Self;
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer<Self>                              Pointer;
  typedef SmartPointer<const Self>                        ConstPointer;
  
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
  itkTypeMacro(DCTPoissonSolverImageFilter, ImageToImageFilter);

  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const;

protected:

  DCTPoissonSolverImageFilter();
  ~DCTPoissonSolverImageFilter(){}

  //  Iterators
  typedef itk::ImageRegionIteratorWithIndex< TInputImage > ItType;
  
  void GenerateData();

private:

  DCTPoissonSolverImageFilter(Self&); // intentionally not implemented
  void operator=(const Self&); // intentionally not implemented
  
  // Component filter types
  typedef itk::DCTImageFilter< TInputImage >                   DCTType;

  typename DCTType::Pointer   m_DCT_Forward;
  typename DCTType::Pointer   m_DCT_Inverse;

};

}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkDCTPoissonSolverImageFilter.txx"
#endif

#endif // __itkDCTPoissonSolverImageFilter_h
