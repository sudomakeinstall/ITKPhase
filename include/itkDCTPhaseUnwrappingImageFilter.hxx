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
::DCTPhaseUnwrappingImageFilter()
{

  m_P = PType::New();
  m_Stats = StatsType::New();
  m_Subtract = SubtractType::New();
  m_Solver = SolverType::New();

}

template < typename TInputImage, typename TOutputImage >
void
DCTPhaseUnwrappingImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
  
  typename TInputImage::ConstPointer input = this->GetInput(); // Save input to variable
  
  // Calculate the Laplacian
  m_P->SetInput( input );

  // Subtract Constant bias
  m_Stats->SetInput( m_P->GetOutput() );
  m_Stats->Update();
  
  double bias = m_Stats->GetMean();
  
  m_Subtract->SetInput1( m_P->GetOutput() );
  m_Subtract->SetConstant2( bias );

  m_Solver->SetInput( m_Subtract->GetOutput() );
  m_Solver->Update();
  
  this->GetOutput()->Graft( m_Solver->GetOutput() );

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
