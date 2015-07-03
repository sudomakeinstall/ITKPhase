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
#ifndef __itkHelmholtzDecompositionImageFilter_txx
#define __itkHelmholtzDecompositionImageFilter_txx

#include "itkHelmholtzDecompositionImageFilter.h"
 
namespace itk {

template< typename TInputImage, typename TOutputImage >
HelmholtzDecompositionImageFilter< TInputImage, TOutputImage >
::HelmholtzDecompositionImageFilter()
{
  /** There are two required outputs for this filter. */
  this->SetNumberOfRequiredOutputs(2);
  
  this->SetNthOutput( 0, this->MakeOutput(0) ); // GetIrrotational()
  this->SetNthOutput( 1, this->MakeOutput(1) ); // GetRotational()
	
  /** There is one required input for this filter. */
  this->SetNumberOfRequiredInputs(1);
}

template< typename TInputImage, typename TOutputImage>
DataObject::Pointer
HelmholtzDecompositionImageFilter< TInputImage, TOutputImage >
::MakeOutput(long unsigned int id)
{
  DataObject::Pointer output;
 
  switch ( id )
    {
    case 0:
      output = ( TOutputImage::New() ).GetPointer();
      break;
    case 1:
      output = ( TOutputImage::New() ).GetPointer();
      break;
    default:
      std::cerr << "No output " << id << std::endl;
      output = NULL;
      break;
    }
  return output.GetPointer();
}

template< typename TInputImage, typename TOutputImage >
TOutputImage*
HelmholtzDecompositionImageFilter< TInputImage, TOutputImage>
::GetIrrotational()
{
  return dynamic_cast< TOutputImage * >( this->ProcessObject::GetOutput(0) );
}

template< typename TInputImage, typename TOutputImage >
TOutputImage*
HelmholtzDecompositionImageFilter< TInputImage, TOutputImage >
::GetRotational()
{
  return dynamic_cast< TOutputImage * >( this->ProcessObject::GetOutput(1) );
}

template< typename TInputImage, typename TOutputImage >
void
HelmholtzDecompositionImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
	
  m_Unwrap = UnwrapType::New();
  m_WrapIrrot = WrapType::New();
  m_Subtract = SubtractType::New();
  m_WrapRot = WrapType::New();
  
  m_Unwrap->SetInput( this->GetInput() );
  m_WrapIrrot->SetInput( m_Unwrap->GetOutput() );
  
  m_WrapIrrot->GraftOutput( this->GetIrrotational() ); // Irrotational
  m_WrapIrrot->Update();
  this->GraftNthOutput(0, m_WrapIrrot->GetOutput() );
  
  m_Subtract->SetInput1( this->GetInput() );
  m_Subtract->SetInput2( m_WrapIrrot->GetOutput() );
  
  m_WrapRot->SetInput( m_Subtract->GetOutput() );
  
  m_WrapRot->GraftOutput( this->GetRotational() ); // Rotational
  m_WrapRot->Update();
  this->GraftNthOutput(1, m_WrapRot->GetOutput() );
  
  this->AllocateOutputs();

} // end GenerateData()

template < typename TInputImage, typename TOutputImage >
void
HelmholtzDecompositionImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "No parameters." << std::endl;
}
 
} // end namespace itk
 
#endif // DV_HelmholtzDecompositionImageFilter_H
