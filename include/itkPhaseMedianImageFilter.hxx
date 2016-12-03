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
#ifndef itkPhaseMedianImageFilter_hxx
#define itkPhaseMedianImageFilter_hxx

namespace itk
{

template< typename TInputImage, typename TOutputImage >
PhaseMedianImageFilter< TInputImage, TOutputImage >
::PhaseMedianImageFilter()
{
  this->m_Radius.Fill(3);
}

template< typename TInputImage, typename TOutputImage >
void
PhaseMedianImageFilter< TInputImage, TOutputImage >
::GenerateData()
{

  typename TInputImage::ConstPointer input = this->GetInput();

  this->m_Sin = SinType::New();
  this->m_Cos = CosType::New();

  this->m_Sin->SetInput( input );
  this->m_Cos->SetInput( input );

  this->m_MedianSin = MedianType::New();
  this->m_MedianCos = MedianType::New();

  this->m_MedianSin->SetInput(  this->m_Sin->GetOutput() );
  this->m_MedianSin->SetRadius( this->m_Radius );

  this->m_MedianCos->SetInput(  this->m_Cos->GetOutput() );
  this->m_MedianCos->SetRadius( this->m_Radius );

  this->m_Atan2 = Atan2Type::New();
  this->m_Atan2->SetInput1( this->m_MedianSin->GetOutput() );
  this->m_Atan2->SetInput2( this->m_MedianCos->GetOutput() );
  this->m_Atan2->Update();

  this->GetOutput()->Graft( this->m_Atan2->GetOutput() );
  
}
 
}// end namespace itk
 
#endif
