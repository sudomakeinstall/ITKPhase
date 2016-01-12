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
#ifndef itkWrappedPhaseLaplacianImageFilter_hxx
#define itkWrappedPhaseLaplacianImageFilter_hxx

#include "itkWrappedPhaseLaplacianImageFilter.h"

namespace itk {

template< typename TInputImage, typename TOutputImage >
WrappedPhaseLaplacianImageFilter< TInputImage, TOutputImage >
::WrappedPhaseLaplacianImageFilter() :
m_Qual(QualType::New()),
m_Weighted(false)
{}

template< typename TInputImage, typename TOutputImage >
void
WrappedPhaseLaplacianImageFilter< TInputImage, TOutputImage >
::GenerateData()
{

  typename TInputImage::ConstPointer input = this->GetInput();
  typename TInputImage::Pointer output = this->GetOutput();
  this->AllocateOutputs();
  output->FillBuffer( 0 );

  this->m_Qual->SetInput( input );
  this->m_Qual->Update();

  typename CNItType::RadiusType radius;
  radius.Fill( 1 );

  CNItType inIt( radius, input, input->GetLargestPossibleRegion() );
  CNItType qualIt( radius, this->m_Qual->GetOutput(), input->GetLargestPossibleRegion() );
  ItType outIt( output, input->GetLargestPossibleRegion() );

  // p. 368-9
  typename CNItType::SizeValueType k = inIt.Size() / 2;

  for (inIt.GoToBegin(), qualIt.GoToBegin(), outIt.GoToBegin();
       !inIt.IsAtEnd();
       ++inIt, ++qualIt, ++outIt )
    {

    for (unsigned int i = 0; i < TInputImage::ImageDimension; ++i)
      {

      const typename TInputImage::IndexType::IndexValueType leftIndex
        = input->GetLargestPossibleRegion().GetIndex()[i];

      const typename TInputImage::IndexType::IndexValueType rightIndex
        = leftIndex + input->GetLargestPossibleRegion().GetSize()[i];

// FIXME

// OLD WAY
// THIS IS THE WAY GIVEN IN THE APPENDIX (P. 369)
// HOWEVER, THE BOUNDARY CONDITION IS SOMEHOW DIFFERENT FROM ITK'S
        typename CNItType::SizeValueType k1 = (inIt.GetIndex()[i] < (rightIndex - 1)) ?
          k + inIt.GetStride(i) : k - inIt.GetStride(i);
  
        typename CNItType::SizeValueType k2 = (inIt.GetIndex()[i] > leftIndex) ?
          k - inIt.GetStride(i) : k + inIt.GetStride(i);
// END OLD WAY

// NEW WAY
// THIS WAY REVERSES THE CALCULATION AT THE BOUNDARIES
//      typename CNItType::SizeValueType k1 = k + inIt.GetStride(i);
//      typename CNItType::SizeValueType k2 = k - inIt.GetStride(i);
//
//      if (!(inIt.GetIndex()[i] < (rightIndex - 1)) || !(inIt.GetIndex()[i] > leftIndex))
//        {
//        typename CNItType::SizeValueType temp = k1;
//        k1 = k2;
//        k2 = temp;
//        }
// END NEW WAY

      if (this->m_Weighted)
        {
        double w1 = qualIt.GetPixel( k1 );
        double w2 = qualIt.GetPixel( k2 );

        const double wCenter = qualIt.GetCenterPixel();
        w1 = (wCenter*wCenter < w1*w1) ? wCenter*wCenter : w1*w1;
        w2 = (wCenter*wCenter < w2*w2) ? wCenter*wCenter : w2*w2;

        outIt.Value() += w1*this->Wrap(inIt.GetPixel( k1 ) - inIt.GetCenterPixel());
        outIt.Value() += w2*this->Wrap(inIt.GetPixel( k2 ) - inIt.GetCenterPixel());
        }
      else
        {
        outIt.Value() += this->Wrap(inIt.GetPixel( k1 ) - inIt.GetCenterPixel());
        outIt.Value() += this->Wrap(inIt.GetPixel( k2 ) - inIt.GetCenterPixel());
        }

      }

    }

}

template < typename TInputImage, typename TOutputImage >
void
WrappedPhaseLaplacianImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const
{

//  Superclass::PrintSelf(os,indent);

  os << indent << "Weighted: " << m_Weighted << std::endl;

}

}// end namespace itk
 
#endif
