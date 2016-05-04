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
#ifndef itkPhaseGradientImageFilter_hxx
#define itkPhaseGradientImageFilter_hxx

#include "itkPhaseGradientImageFilter.h"
 
namespace itk {

template< typename TInputImage, typename TOutputImage >
PhaseGradientImageFilter< TInputImage, TOutputImage >
::PhaseGradientImageFilter()
{

}

template< typename TInputImage, typename TOutputImage >
void
PhaseGradientImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
 
  auto input = TInputImage::New();
  input->Graft( this->GetInput() );
  input->DisconnectPipeline();

  // Shifted
  auto add = TAdd::New();
  auto wrap = TWrap::New();

  add->SetInput1( this->GetInput() );
  add->SetConstant2( M_PI );
  wrap->SetInput( add->GetOutput() );
  wrap->Update();

  auto input_shifted = TInputImage::New();
  input_shifted->Graft( wrap->GetOutput() );
  input_shifted->DisconnectPipeline();

  auto input_mag = TInputImage::New();
  auto input_mag_shifted = TInputImage::New();
  auto input_grad = TOutputImage::New();
  auto input_grad_shifted = TOutputImage::New();

    {
    auto gradient = TGradient::New();
    auto magnitude = TMagnitude::New();

    gradient->SetInput( input );
    magnitude->SetInput( gradient->GetOutput() );
    magnitude->Update();
    input_mag->Graft( magnitude->GetOutput() );
    input_mag->DisconnectPipeline();
    input_grad->Graft( gradient->GetOutput() );
    input_grad->DisconnectPipeline();
    }

    {
    auto gradient = TGradient::New();
    auto magnitude = TMagnitude::New();

    gradient->SetInput( input_shifted );
    magnitude->SetInput( gradient->GetOutput() );
    magnitude->Update();
    input_mag_shifted->Graft( magnitude->GetOutput() );
    input_mag_shifted->DisconnectPipeline();
    input_grad_shifted->Graft( gradient->GetOutput() );
    input_grad_shifted->DisconnectPipeline();
    }

  auto mask = TMinMask::New();
  mask->SetInput1( input_mag );
  mask->SetInput2( input_mag_shifted );

  auto choose = TChoose::New();
  choose->SetInput1( mask->GetOutput() );
  choose->SetInput2( input_grad );
  choose->SetInput3( input_grad_shifted );
  choose->Update();

  choose->GraftOutput( this->GetOutput() );
  this->AllocateOutputs();
  choose->Update();

}

template < typename TInputImage, typename TOutputImage > 
void 
PhaseGradientImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const 
{

  Superclass::PrintSelf(os,indent); 
  
}
 
}// end namespace itk
 
#endif
