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
#ifndef itkDCTImageFilter_hxx
#define itkDCTImageFilter_hxx

#include "itkDCTImageFilter.h"

namespace itk 
{ 

template < typename TInputImage, typename TOutputImage >
DCTImageFilter< TInputImage, TOutputImage >
::DCTImageFilter()
:
m_TransformDirection(Forward),
m_Divide(DivideType::New())
{} 

template < typename TInputImage, typename TOutputImage > 
void 
DCTImageFilter< TInputImage, TOutputImage >
::GenerateData() 
{ 

  // Configure the I/O
  typename TInputImage::ConstPointer input = this->GetInput();
  typename TInputImage::Pointer output = this->GetOutput();

  // FIXME: Is this necessary?  Would this->AllocateOutputs() work instead? 
  output->SetRegions( input->GetLargestPossibleRegion() );
  output->Allocate();
  
  const typename TInputImage::SizeValueType NUMPIX
    = input->GetLargestPossibleRegion().GetNumberOfPixels();

  typename TInputImage::PixelType *in, *out;
  in = (typename TInputImage::PixelType*)
    fftw_malloc(sizeof(typename TInputImage::PixelType) * NUMPIX);
  out = (typename TInputImage::PixelType*)
    fftw_malloc(sizeof(typename TInputImage::PixelType) * NUMPIX);

  in = (typename TInputImage::PixelType*)input->GetBufferPointer();
  out = (typename TInputImage::PixelType*)output->GetBufferPointer();

  fftw_r2r_kind kind[TInputImage::ImageDimension];
  int n[TInputImage::ImageDimension];

  for (unsigned int d = 0; d < TInputImage::ImageDimension; ++d)
    {

    // Why is this backwards?  I thought that both c++ and fftw were row order.
    n[TInputImage::ImageDimension - 1 - d] = input->GetLargestPossibleRegion().GetSize()[d];
    kind[d] = (Reverse == this->m_TransformDirection) ? FFTW_REDFT01 : FFTW_REDFT10;

    }

  fftw_plan p = fftw_plan_r2r( TInputImage::ImageDimension, // rank
                               n, // pointer to array of rank integers
                               in,
                               out,
                               kind,
                               FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  
  if (Reverse == this->m_TransformDirection)
    {
 
    const double NORM = NUMPIX*pow(2, TInputImage::ImageDimension);

    // FIXME: Why are we setting output instead of input?
    this->m_Divide->SetInput( output );
    this->m_Divide->SetConstant( NORM );
    this->m_Divide->Update();
    this->GetOutput()->Graft( this->m_Divide->GetOutput() );
    
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

#endif
