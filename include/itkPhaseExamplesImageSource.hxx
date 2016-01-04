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
#ifndef itkPhaseExamplesImageSource_hxx
#define itkPhaseExamplesImageSource_hxx

#include "itkPhaseExamplesImageSource.h"
 
namespace itk {

template< typename TImage >
PhaseExamplesImageSource< TImage >
::PhaseExamplesImageSource()
{

  this->Reset();

}

template< typename TImage >
void
PhaseExamplesImageSource< TImage >
::Reset()
{

  m_Wrap = true;
  m_Shear = false;
  m_Noise = false;
  m_NoiseSD = vnl_math::pi / 2;
  m_NoiseMean = 0;
  m_NoiseSeed = 0;

}

template< typename TImage >
void
PhaseExamplesImageSource< TImage >
::GenerateData()
{

  typename TImage::Pointer phase = this->GetOutput();

  typename TImage::IndexType index;
  typename TImage::SizeType size;
  
  index.Fill( 0 );
  size.Fill( 256 );
  
  typename TImage::RegionType region( index, size );
  
  phase->SetRegions( region );
  phase->Allocate();
  phase->FillBuffer( 0 );
  
  ItType it( phase, phase->GetLargestPossibleRegion() );
  for (it.GoToBegin(); !it.IsAtEnd(); ++it) {  
  
    it.Set( 4*vnl_math::pi - 8*vnl_math::pi*it.GetIndex()[0]/(size[0] - 1) );
  
  }
  
  if (m_Shear)
    {
  
    size[1] = 64;
    region.SetSize( size );

    index[1] = 96;
    region.SetIndex( index );

    ItType it2( phase, region );

    for (it2.GoToBegin(); !it2.IsAtEnd(); ++it2)
      {
      it2.Value() *= -1;
      }

    }
  
  if (m_Noise)
    {
   
    index.Fill( 64 );
    size.Fill( 64 );
    
    typename TImage::RegionType noiseRegion( index, size );

    m_ROIFilter = ROIType::New();
    m_ROIFilter->SetInput( phase );
    m_ROIFilter->SetRegionOfInterest( noiseRegion );
    
    m_NoiseFilter = NoiseType::New();
    m_NoiseFilter->SetMean( m_NoiseMean );
    m_NoiseFilter->SetStandardDeviation( m_NoiseSD );
    m_NoiseFilter->SetSeed( m_NoiseSeed );
    m_NoiseFilter->SetInput( m_ROIFilter->GetOutput() );
    m_NoiseFilter->Update(); // Required
    
    m_PasteFilter = PasteType::New();
    m_PasteFilter->SetSourceImage( m_NoiseFilter->GetOutput() );
    m_PasteFilter->SetDestinationImage( phase );
    m_PasteFilter->SetSourceRegion( m_NoiseFilter->GetOutput()->GetLargestPossibleRegion() );
    m_PasteFilter->SetDestinationIndex( index );
    m_PasteFilter->Update();

    this->GraftOutput( m_PasteFilter->GetOutput() );

    }
  
  if (m_Wrap)
    {
  
    m_WrapFilter = WrapType::New();
    m_WrapFilter->SetInput( this->GetOutput() );
    m_WrapFilter->Update();
    
    this->GraftOutput( m_WrapFilter->GetOutput() );
  
    }
 
}

template < typename TImage >
void
PhaseExamplesImageSource< TImage >
::PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "Shear: " << m_Shear << std::endl;
  os << indent << "Noise: " << m_Noise << std::endl;
  os << indent << "Noise SD: " << m_NoiseSD << std::endl;
  os << indent << "Wrap: " << m_Wrap << std::endl;
  os << indent << "Noise Mean: " << m_NoiseMean << std::endl;
  os << indent << "Noise Seed: " << m_NoiseSeed << std::endl;
  
}
 
} // end namespace itk
 
#endif
