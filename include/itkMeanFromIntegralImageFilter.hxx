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
#ifndef itkMeanFromIntegralImageFilter_hxx
#define itkMeanFromIntegralImageFilter_hxx

#include "itkMeanFromIntegralImageFilter.h"

#include "itkConstNeighborhoodIterator.h"
#include "itkConstShapedNeighborhoodIterator.h"
#include "itkNeighborhoodInnerProduct.h"
#include "itkImageRegionIterator.h"
#include "itkOffset.h"
#include "itkProgressReporter.h"

namespace itk
{
template< typename TInputImage, typename TOutputImage >
MeanFromIntegralImageFilter< TInputImage, TOutputImage >
::MeanFromIntegralImageFilter()
{}

template< typename TInputImage, typename TOutputImage >
void
MeanFromIntegralImageFilter< TInputImage, TOutputImage  >
::ConstructSideLengthsMatrix( ConstNeighborhoodIterator< TInputImage > it )
{

  this->m_SideLengths.SetSize( 1, TInputImage::ImageDimension );
  for ( unsigned int i = 0; i < TInputImage::ImageDimension; ++i) {
    m_SideLengths(0, i) = ( m_Radius[i] * 2 - 1) * it.GetStride( i );
  }

}

template< typename TInputImage, typename TOutputImage >
void
MeanFromIntegralImageFilter< TInputImage, TOutputImage >
::ConstructCombinationsMatrix( )
{
  this->m_Combinations.SetSize( TInputImage::ImageDimension, pow(2, TInputImage::ImageDimension ) );

  for (unsigned int i = 0; i < pow(2, TInputImage::ImageDimension); ++i)
    {
    std::bitset<TInputImage::ImageDimension> x(i);
    for (unsigned int ii = 0; ii < TInputImage::ImageDimension; ++ii)
      {
      this->m_Combinations(ii, i) = x[ii];
      }
    }

}

template< typename TInputImage, typename TOutputImage >
void
MeanFromIntegralImageFilter< TInputImage, TOutputImage >
::CalculateCorners( )
{
  this->m_Corners.SetSize( this->m_SideLengths.Rows(), this->m_Combinations.Cols() );
  this->m_Corners = this->m_SideLengths * this->m_Combinations;
}

template< typename TInputImage, typename TOutputImage >
void
MeanFromIntegralImageFilter< TInputImage, TOutputImage >
::CalculateSigns( )
{
  VariableSizeMatrix< long > Ones;
  Ones.SetSize( 1, TInputImage::ImageDimension );
  Ones.Fill( 1 );

  m_Signs.SetSize( Ones.Rows(), m_Combinations.Cols() );
  m_Signs = Ones * m_Combinations;

  int factor = (m_Signs(0, (pow(2, TInputImage::ImageDimension) - 1)) % 2) ? 1 : -1;

  for ( int i = 0; i < pow(2, TInputImage::ImageDimension); ++i)
    {
    m_Signs(0,i) %= 2;
    m_Signs(0,i) *= 2;
    m_Signs(0,i) -= 1;
    m_Signs(0,i) *= factor;
    }

}

template< typename TInputImage, typename TOutputImage >
void
MeanFromIntegralImageFilter< TInputImage, TOutputImage >
::BeforeThreadedGenerateData()
{

  ConstNeighborhoodIterator< TInputImage > bit(m_Radius,
                                               this->GetInput(),
                                               this->GetInput()->GetLargestPossibleRegion());
  
  ConstructSideLengthsMatrix( bit );
  ConstructCombinationsMatrix();
  CalculateCorners();
  CalculateSigns();
  
}

template< typename TInputImage, typename TOutputImage >
void
MeanFromIntegralImageFilter< TInputImage, TOutputImage >
::ThreadedGenerateData(const OutputImageRegionType & outputRegionForThread,
                       ThreadIdType itkNotUsed(threadId))
{

  // Allocate output
  typename TInputImage::ConstPointer input = this->GetInput();
  typename TOutputImage::Pointer output = this->GetOutput();
  this->AllocateOutputs();

  ConstShapedNeighborhoodIterator< TInputImage > nit( m_Radius,
                                                      input,
                                                      outputRegionForThread );

  ImageRegionIterator< TOutputImage > outIt( output, outputRegionForThread );

  for (unsigned int i = 0; i < m_Corners.Cols(); ++i)
    {
    nit.ActivateOffset( nit.GetOffset( m_Corners(0,i) ) );
    }

  outIt.GoToBegin();
  nit.GoToBegin();
  double nsum;
  
  while ( !nit.IsAtEnd() )
    {

    nsum = 0;

    for ( int i = 0; i < pow(2, TInputImage::ImageDimension); ++i)
      {
      nsum += m_Signs(0,i) * nit.GetPixel( m_Corners(0,i) );
      }

    outIt.Set( static_cast< typename TOutputImage::PixelType >( nsum ) );

    ++outIt;
    ++nit;

  }
  
}

} // end namespace itk

#endif
