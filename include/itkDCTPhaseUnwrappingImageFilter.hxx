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
#ifndef itkDCTPhaseUnwrappingImageFilter_hxx
#define itkDCTPhaseUnwrappingImageFilter_hxx

#include "itkDCTPhaseUnwrappingImageFilter.h"

namespace itk
{

template < typename TInputImage, typename TOutputImage >
DCTPhaseUnwrappingImageFilter< TInputImage, TOutputImage >
::DCTPhaseUnwrappingImageFilter() :
m_P(PType::New()),
m_Stats(StatsType::New()),
m_Subtract(SubtractType::New()),
m_Solver(SolverType::New())
{}

template < typename TInputImage, typename TOutputImage >
void
DCTPhaseUnwrappingImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
  
  // Calculate the Laplacian
  this->m_P->SetInput( this->GetInput() );

  // Subtract Constant bias
  this->m_Stats->SetInput( this->m_P->GetOutput() );
  this->m_Stats->Update();
  
  const double BIAS = this->m_Stats->GetMean();
  
  this->m_Subtract->SetInput1( this->m_P->GetOutput() );
  this->m_Subtract->SetConstant2( BIAS );

  this->m_Solver->SetInput( this->m_Subtract->GetOutput() );
  this->m_Solver->Update();
  
  this->GetOutput()->Graft( this->m_Solver->GetOutput() );

}

//  PrintSelf method prints parameters

template < typename TInputImage, typename TOutputImage >
void
DCTPhaseUnwrappingImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf(os,indent);

}

} /* end namespace itk */

#endif
