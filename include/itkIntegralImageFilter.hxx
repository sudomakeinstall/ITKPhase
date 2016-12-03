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
#ifndef itkIntegralImageFilter_hxx
#define itkIntegralImageFilter_hxx

#include "itkIntegralImageFilter.h"
#include "itkImageAlgorithm.h"

namespace itk 
{ 

template < typename TInputImage, typename TOutputImage > 
void 
IntegralImageFilter< TInputImage, TOutputImage >
::SumSingleDimension( unsigned int i, ItType m_it )
{

  typename TOutputImage::PixelType temp;

  m_it.SetDirection( i );
  m_it.GoToBegin();

  while ( !m_it.IsAtEnd() )
    {

    m_it.GoToBeginOfLine();
    temp = 0.0;

    while ( !m_it.IsAtEndOfLine() )
      {

      temp += m_it.Get();
      m_it.Set( temp );

      ++m_it;

      }

    m_it.NextLine();

  }

}

template < typename TInputImage, typename TOutputImage > 
void 
IntegralImageFilter< TInputImage, TOutputImage >
::GenerateData() 
{ 

  // Configure the I/O
  typename TInputImage::ConstPointer input = this->GetInput();
  typename TOutputImage::Pointer output = this->GetOutput();

  this->AllocateOutputs();
 
  ImageAlgorithm::Copy(input.GetPointer(),
                       output.GetPointer(),
                       output->GetRequestedRegion(),
                       output->GetRequestedRegion() );

  ItType m_it(output, output->GetLargestPossibleRegion());

  for (unsigned int i = 0; i < TOutputImage::ImageDimension; ++i)
    {
    this->SumSingleDimension( i, m_it );
    }

}

//  PrintSelf method prints parameters 

template < typename TInputImage, typename TOutputImage > 
void 
IntegralImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const 
{ 
  Superclass::PrintSelf(os,indent); 

  os 
    << indent << "No parameters." 
    << std::endl; 
} 

} /* end namespace itk */ 

#endif // __itkIntegralImageFilter_hxx
