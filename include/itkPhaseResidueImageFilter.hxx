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
#ifndef itkPhaseResidueImageFilter_hxx
#define itkPhaseResidueImageFilter_hxx
 
namespace itk {

template< class TInputImage, class TOutputImage >
PhaseResidueImageFilter< TInputImage, TOutputImage >
::PhaseResidueImageFilter()
{}
 
template< class TInputImage, class TOutputImage >
void PhaseResidueImageFilter< TInputImage, TOutputImage >
::GenerateData()
{

  typename TInputImage::ConstPointer input = this->GetInput();
  typename TOutputImage::Pointer output = this->GetOutput();
  output->SetRegions( input->GetLargestPossibleRegion() );
  output->Allocate();
  output->FillBuffer( 0 );
    
  typename TInputImage::SizeType radius;
  radius.Fill( 1 );
  
  typename TInputImage::RegionType region = input->GetLargestPossibleRegion();
  typename TInputImage::SizeType ones;
  ones.Fill( 1 );
  
  region.GetModifiableSize() -= ones;
  
  ConstItType inIt(radius, input, region );
  ItType outIt(output, region );
  
  inIt.GoToBegin();
  outIt.GoToBegin();

  typename ConstItType::OffsetType UL = {{0, 0}};
  typename ConstItType::OffsetType UR = {{1, 0}};
  typename ConstItType::OffsetType LL = {{0, 1}};
  typename ConstItType::OffsetType LR = {{1, 1}};

  while( !inIt.IsAtEnd() ) {

    double d1 = this->Wrap( inIt.GetPixel(LL) - inIt.GetPixel(UL) );
    double d2 = this->Wrap( inIt.GetPixel(LR) - inIt.GetPixel(LL) );
    double d3 = this->Wrap( inIt.GetPixel(UR) - inIt.GetPixel(LR) );
    double d4 = this->Wrap( inIt.GetPixel(UL) - inIt.GetPixel(UR) );

    double sum = d1 + d2 + d3 + d4;
    
    if (sum < -1) {
    
      sum = -1;
      
    } else if (sum < 1) {
    
      sum = 0;
    
    } else {
    
      sum = 1;
      
    }

    outIt.Set( sum );

    ++inIt;
    ++outIt;

  }
 
}

template < typename TInputImage, typename TOutputImage > 
void 
PhaseResidueImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const 
{

  Superclass::PrintSelf(os,indent); 

  os << indent << "No additional parameters." << std::endl;
  
}
 
}// end namespace itk
 
#endif
