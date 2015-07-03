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
#ifndef __itkWrappedPhaseLaplacianImageFilter_txx
#define __itkWrappedPhaseLaplacianImageFilter_txx
 
namespace itk {

template< typename TInputImage, typename TOutputImage >
WrappedPhaseLaplacianImageFilter< TInputImage, TOutputImage >
::WrappedPhaseLaplacianImageFilter() 
{
  
  // Set Defaults
  m_Weighted = false; 

}

template< typename TInputImage, typename TOutputImage >
void
WrappedPhaseLaplacianImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
  
  typename TInputImage::ConstPointer input = this->GetInput();
  typename TInputImage::Pointer output = this->GetOutput();
  output->SetRegions( input->GetLargestPossibleRegion() );
  output->Allocate();
  output->FillBuffer( 0 );
  
  this->AllocateOutputs();

  m_Qual = QualType::New();
  m_Qual->SetInput( input );
  m_Qual->Update();

  typename CNItType::RadiusType radius;
  radius.Fill( 1 );
  
  CNItType inIt( radius, input, input->GetLargestPossibleRegion() );
  CNItType qualIt( radius, m_Qual->GetOutput(), input->GetLargestPossibleRegion() );
  ItType outIt( output, input->GetLargestPossibleRegion() );
  inIt.GoToBegin();
  qualIt.GoToBegin();
  outIt.GoToBegin();
  
  // p. 368-9
  typename CNItType::SizeValueType k = inIt.Size() / 2;
  typename CNItType::SizeValueType k1, k2;
  double w1, w2;
  w1 = w2 = 1;
 
  while( !inIt.IsAtEnd() ) {
   
    for (unsigned int i = 0; i < TInputImage::ImageDimension; ++i) {
     
      typename TInputImage::IndexType::IndexValueType leftIndex;
      leftIndex = input->GetLargestPossibleRegion().GetIndex()[i];
      typename TInputImage::IndexType::IndexValueType rightIndex;
      rightIndex = leftIndex + input->GetLargestPossibleRegion().GetSize()[i];
       
     // if (inIt.GetIndex()[i] < input->GetLargestPossibleRegion().GetSize()[i] - 1) {
      if (inIt.GetIndex()[i] < rightIndex - 1) {
        k1 = k + inIt.GetStride( i );
      } else {
        k1 = k - inIt.GetStride( i );
      }

     // if (inIt.GetIndex()[i] > 0) {
      if (inIt.GetIndex()[i] > leftIndex) {
        k2 = k - inIt.GetStride( i );
      } else {
        k2 = k + inIt.GetStride( i );
      }
      
      if (m_Weighted) {
    
        w1 = qualIt.GetPixel( k1 );
        w2 = qualIt.GetPixel( k2 );
          
        double wCenter = qualIt.GetCenterPixel();
        w1 = (wCenter*wCenter < w1*w1) ? wCenter*wCenter : w1*w1;
        w2 = (wCenter*wCenter < w2*w2) ? wCenter*wCenter : w2*w2;

      }      
    
      outIt.Value() += w1*this->Wrap(inIt.GetPixel( k1 ) - inIt.GetCenterPixel());
      outIt.Value() += w2*this->Wrap(inIt.GetPixel( k2 ) - inIt.GetCenterPixel());
    
    }
    
    ++inIt;
    ++qualIt;
    ++outIt;
  
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
