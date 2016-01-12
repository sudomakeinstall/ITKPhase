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
#ifndef itkDCTPoissonSolverImageFilter_hxx
#define itkDCTPoissonSolverImageFilter_hxx

#include "itkDCTPoissonSolverImageFilter.h"

namespace itk
{

template < typename TInputImage, typename TOutputImage >
DCTPoissonSolverImageFilter< TInputImage, TOutputImage >
::DCTPoissonSolverImageFilter() :
m_DCT_Forward(DCTType::New()),
m_DCT_Inverse(DCTType::New())
{

  this->m_DCT_Forward->SetTransformDirection( DCTType::Forward );
  this->m_DCT_Inverse->SetTransformDirection( DCTType::Reverse );

}

template < typename TInputImage, typename TOutputImage >
void
DCTPoissonSolverImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
  
  typename TInputImage::ConstPointer input = this->GetInput(); // Save input to variable
  
  // Calculate the forward DCT
  this->m_DCT_Forward->SetInput( input );
  this->m_DCT_Forward->Update();

  // Save the transformed data to an image for iteration 
  typename TInputImage::Pointer transformed = TInputImage::New();
  transformed->Graft( m_DCT_Forward->GetOutput() );
  transformed->Update();

  // Get the dimensions of the image
  const typename TInputImage::SizeType size = input->GetLargestPossibleRegion().GetSize();
  const typename TInputImage::IndexType index = input->GetLargestPossibleRegion().GetIndex();

  // Iterate through the temp image
  // See equation 5.60, p. 200
  ItType it(transformed, transformed->GetLargestPossibleRegion() );
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
    {

    typename TInputImage::PixelType var = -2*TInputImage::ImageDimension;

    for (unsigned int i = 0; i < TInputImage::ImageDimension; ++i)
      {
      var += 2*cos(vnl_math::pi*(it.GetIndex()[i] - index[i]) / size[i]);
      } // 5.60, p.200

    it.Value() /= var; // Divide by the result

    }

  std::cout << transformed->GetLargestPossibleRegion() << std::endl;
  for (unsigned int r = 0; r < 10; ++r)
    for (unsigned int c = 0; c < 10; ++c)
      std::cout << transformed->GetPixel({r,c}) << std::endl;

//  // Set the zero index to "0"
//  typename TInputImage::IndexType zeroIndex;
//  zeroIndex.Fill( 0 );
//  transformed->SetPixel( zeroIndex, 0 );
  transformed->SetPixel( index, 0 );

  // Take the inverse DCT
  this->m_DCT_Inverse->SetInput( transformed );
  this->m_DCT_Inverse->Update();
  
  this->GetOutput()->Graft( this->m_DCT_Inverse->GetOutput() );

}

//  PrintSelf method prints parameters

template < typename TInputImage, typename TOutputImage >
void
DCTPoissonSolverImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "No parameters." << std::endl;
}

} /* end namespace itk */

#endif
