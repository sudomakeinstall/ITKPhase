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
#ifndef __itkPhaseResidueImageFilter_h
#define __itkPhaseResidueImageFilter_h
 
#include "itkPhaseImageToImageFilter.h"
#include "itkObjectFactory.h"
#include "itkConstNeighborhoodIterator.h"
#include "itkImageRegionIterator.h"

namespace itk
{
/** \class PhaseResidueImageFilter
 * \brief Calculates phase residues for each pixel in an image.  Only meaningful for 2D images.
 *
 * This filter assumes a phase image wrapped into the range of -pi to pi as input and
 * calculates phase residues for each pixel in the image.
 *
 * For each pixel, this algorithm traverses a counterclockwise path within a 2x2 region where
 * the pixel of interest is the "upper left" corner.  For each pair of pixels, the unwrapped
 * phase difference is calculated.  These unwrapped phase differences are then summed
 * for each neighborhood.  A sum of zero indicates no residue, a positive sum indicates
 * a positive dipole, and a negative sum indicates a negative dipole.
 *
 * Phase residues are useful for determining whether wrapped phase can be unwrapped
 * in a path-independent manner.  A 2D image containing no phase residues can be unwrapped
 * along any path, yielding the same answer.  The presence of a residue indicates that the
 * answer obtained is dependent upon the path taken.  Phase residues are also useful
 * for defining the most appropriate path.  For example, in some unwrapping algorithms,
 * dipoles (pairs of nearby positive and negative phase residues) are connected by
 * "branch cuts," or lines of pixels across which phase unwrapping is forbidden.
 *
 */
template< class TInputImage, class TOutputImage = TInputImage >
class PhaseResidueImageFilter:
public PhaseImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef PhaseResidueImageFilter                              Self;
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
  itkTypeMacro(PhaseResidueImageFilter, PhaseImageToImageFilter);
  
  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const;
 
protected:

  PhaseResidueImageFilter();
  ~PhaseResidueImageFilter(){}
  
  /** Does the real work. */
  void GenerateData();
 
private:

  PhaseResidueImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented
 
  typedef ConstNeighborhoodIterator< TInputImage > ConstItType;
  typedef ImageRegionIterator< TOutputImage >      ItType;

};
} //namespace ITK
 
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPhaseResidueImageFilter.txx"
#endif
 
#endif
