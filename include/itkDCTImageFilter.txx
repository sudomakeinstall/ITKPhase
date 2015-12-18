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
#ifndef __itkDCTImageFilter_txx
#define __itkDCTImageFilter_txx

#include "itkDCTImageFilter.h"

namespace itk 
{ 

template < typename TInputImage, typename TOutputImage >
DCTImageFilter< TInputImage, TOutputImage >
::DCTImageFilter() 
{ 

  m_TransformDirection = Forward;

  // This is where you define filters you need
  // Instantiate them in the GenerateData() step
  m_Divide = DivideType::New();
        
} 

template < typename TInputImage, typename TOutputImage > 
void 
DCTImageFilter< TInputImage, TOutputImage >
::GenerateData() 
{ 

  // Configure the I/O
  typename TInputImage::ConstPointer input = this->GetInput();
  typename TInputImage::Pointer output = this->GetOutput();
 
  output->SetRegions( input->GetLargestPossibleRegion() );
  
  output->Allocate();
  
  typename TInputImage::SizeValueType numpix = input->GetLargestPossibleRegion().GetNumberOfPixels();
	
  typename TInputImage::PixelType *in, *out;
  in = (typename TInputImage::PixelType*) fftw_malloc(sizeof(typename TInputImage::PixelType) * numpix);
  out = (typename TInputImage::PixelType*) fftw_malloc(sizeof(typename TInputImage::PixelType) * numpix);
	
  in = (typename TInputImage::PixelType*)input->GetBufferPointer();
  out = (typename TInputImage::PixelType*)output->GetBufferPointer();
	
  fftw_r2r_kind kind[TInputImage::ImageDimension];
  int n[TInputImage::ImageDimension];
	
  for (unsigned int i = 0; i < TInputImage::ImageDimension; ++i) {
  
    // Why is this backwards?  I thought that both c++ and fftw were row order.
    n[TInputImage::ImageDimension - 1 - i] = input->GetLargestPossibleRegion().GetSize()[i];
    if (m_TransformDirection == Reverse) {
    
      kind[i] = FFTW_REDFT01;
      
    } else {
      
      kind[i] = FFTW_REDFT10;
      
    }

  }
	
  fftw_plan p = fftw_plan_r2r( TInputImage::ImageDimension, // rank
	                          n, // pointer to array of rank integers
	                          in,
	                          out,
	                          kind,
	                          FFTW_ESTIMATE);
  fftw_execute(p);    	
  fftw_destroy_plan(p);
  
  if (Reverse == m_TransformDirection) {
 
    double norm = numpix*pow(2, TInputImage::ImageDimension);

    m_Divide->SetInput( output );
    m_Divide->SetConstant( norm );
    m_Divide->Update();
    this->GetOutput()->Graft( m_Divide->GetOutput() );
    
  }
	
} 

//  PrintSelf method prints parameters 

template < typename TInputImage, typename TOutputImage > 
void 
DCTImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const 
{

  Superclass::PrintSelf(os,indent); 

  os << indent << "Transform Direction: " << m_TransformDirection << std::endl;
  
}

} /* end namespace itk */ 

#endif // __itkDCTImageFilter_txx
