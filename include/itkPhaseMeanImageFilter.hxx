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
#ifndef itkPhaseMeanImageFilter_hxx
#define itkPhaseMeanImageFilter_hxx

#include "itkPhaseMeanImageFilter.h"

namespace itk
{
/** \class PhaseMeanImageFilter
 * \brief Calculates the average wrapped phase in an nxn neighborhood.
 *
 * \ingroup ITKPhase
 */

template< typename TInputImage, typename TOutputImage >
PhaseMeanImageFilter< TInputImage, TOutputImage >
::PhaseMeanImageFilter()
{
  this->m_Radius.Fill(3);
}

template< typename TInputImage, typename TOutputImage >
void
PhaseMeanImageFilter< TInputImage, TOutputImage >
::GenerateData()
{

  typename TInputImage::ConstPointer input = this->GetInput();

  this->m_Sin = SinType::New();
  this->m_Cos = CosType::New();

  this->m_Sin->SetInput( input );
  this->m_Cos->SetInput( input );

  this->m_Sin_Int = IntegralType::New();
  this->m_Cos_Int = IntegralType::New();

  this->m_Sin_Int->SetInput( this->m_Sin->GetOutput() );
  this->m_Cos_Int->SetInput( this->m_Cos->GetOutput() );

  this->m_MeanSin = MeanType::New();
  this->m_MeanCos = MeanType::New();

  typename TInputImage::SizeType ones;
  ones.Fill( 1 );

  this->m_Radius += ones;

  this->m_MeanSin->SetInput(  this->m_Sin_Int->GetOutput() );
  this->m_MeanSin->SetRadius( this->m_Radius );
  this->m_MeanCos->SetInput(  this->m_Cos_Int->GetOutput() );
  this->m_MeanCos->SetRadius( this->m_Radius );

  this->m_Atan2 = Atan2Type::New();
  this->m_Atan2->SetInput1( this->m_MeanSin->GetOutput() );
  this->m_Atan2->SetInput2( this->m_MeanCos->GetOutput() );
  this->m_Atan2->Update();

  this->GetOutput()->Graft( this->m_Atan2->GetOutput() );

}
 
}// end namespace itk
 
#endif
