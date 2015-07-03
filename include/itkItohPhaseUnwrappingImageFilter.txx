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
#ifndef __itkItohPhaseUnwrappingImageFilter_txx
#define __itkItohPhaseUnwrappingImageFilter_txx
 
namespace itk {

template < typename TInputImage, typename TOutputImage >
ItohPhaseUnwrappingImageFilter< TInputImage, TOutputImage >
::ItohPhaseUnwrappingImageFilter() 
{

  m_Direction = 0;

}
 
template< typename TInputImage, typename TOutputImage >
void
ItohPhaseUnwrappingImageFilter< TInputImage, TOutputImage >
::GenerateData()
{

  typename TInputImage::ConstPointer input = this->GetInput();
  typename TOutputImage::Pointer output = this->GetOutput();
  output->SetRegions( input->GetLargestPossibleRegion() );
  output->Allocate();
  
  ImageAlgorithm::Copy(input.GetPointer(),
                  output.GetPointer(),
                  input->GetLargestPossibleRegion(),
                  input->GetLargestPossibleRegion());

  OutItType outIt(output, input->GetLargestPossibleRegion() );

  outIt.SetDirection( m_Direction );

  outIt.GoToBegin();
  
  while (!outIt.IsAtEnd()) {
    
    
    double previous = outIt.Get();

    ++outIt;
    
    while (!outIt.IsAtEndOfLine() ) {
    
      outIt.Set( this->Unwrap( outIt.Get(), previous ) );
      previous = outIt.Get();

      ++outIt;
    
    }
    
    outIt.NextLine();
  
  }
 
}

template < typename TInputImage, typename TOutputImage >
void
ItohPhaseUnwrappingImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "Direction: " << m_Direction << std::endl;
}
 
}// end namespace itk
 
#endif
