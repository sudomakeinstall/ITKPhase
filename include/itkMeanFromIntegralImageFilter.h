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
#ifndef itkMeanFromIntegralImageFilter_h
#define itkMeanFromIntegralImageFilter_h

#include "itkPhaseImageToImageFilter.h"
#include "itkNumericTraits.h"
#include "itkVariableSizeMatrix.h"
#include "itkNeighborhoodAlgorithm.h"
#include <bitset>

namespace itk
{
/** \class MeanFromIntegralImageFilter
 * \brief Applies an averaging filter to an image
 *
 * Computes an image where a given pixel is the mean value of the
 * the pixels in a neighborhood about the corresponding input pixel.
 *
 * \ingroup ITKPhase
 *
 */
template< typename TInputImage, typename TOutputImage >
class MeanFromIntegralImageFilter:
public PhaseImageToImageFilter< TInputImage, TOutputImage >
{
public:

  /** Standard class typedefs. */
  typedef MeanFromIntegralImageFilter                     Self;
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                            Pointer;
  typedef SmartPointer< const Self >                      ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MeanFromIntegralImageFilter, PhaseImageToImageFilter);

  typedef typename TInputImage::RegionType  InputImageRegionType;
  typedef typename TOutputImage::RegionType OutputImageRegionType;
  
  /** Set the index of a pixel with high phase quality. */
  itkSetMacro( Radius, typename TInputImage::SizeType );

  /** Get the index of a pixel with high phase quality. */
  itkGetMacro( Radius, typename TInputImage::SizeType );

#ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( InputHasNumericTraitsCheck,
                   ( Concept::HasNumericTraits< typename TInputImage::PixelType > ) );
  // End concept checking
#endif

protected:
  MeanFromIntegralImageFilter();
  virtual ~MeanFromIntegralImageFilter() {}

  /** MeanFromIntegralImageFilter can be implemented as a multithreaded filter.
   * Therefore, this implementation provides a ThreadedGenerateData()
   * routine which is called for each processing thread. The output
   * image data is allocated automatically by the superclass prior to
   * calling ThreadedGenerateData().  ThreadedGenerateData can only
   * write to the portion of the output image specified by the
   * parameter "outputRegionForThread"
   *
   * \sa BoxImageFilter::ThreadedGenerateData(),
   *     BoxImageFilter::GenerateData() */
   
  void BeforeThreadedGenerateData() ITK_OVERRIDE;
  void ThreadedGenerateData(const OutputImageRegionType & outputRegionForThread,
                            ThreadIdType threadId) ITK_OVERRIDE;
                            
  void ConstructSideLengthsMatrix( ConstNeighborhoodIterator< TInputImage > it );
  void ConstructCombinationsMatrix();
  void CalculateCorners();
  void CalculateSigns();

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(MeanFromIntegralImageFilter);
  
  VariableSizeMatrix< long > m_SideLengths;
  VariableSizeMatrix< long > m_Combinations;
  VariableSizeMatrix< long > m_Corners;
  VariableSizeMatrix< long > m_Signs;
  
  typename TInputImage::SizeType m_Radius;

};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMeanFromIntegralImageFilter.hxx"
#endif

#endif
