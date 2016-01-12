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
#ifndef itkPCGPhaseUnwrappingImageFilter_hxx
#define itkPCGPhaseUnwrappingImageFilter_hxx

#include "itkPCGPhaseUnwrappingImageFilter.h"
 
namespace itk {

template< typename TImage >
PCGPhaseUnwrappingImageFilter< TImage >
::PCGPhaseUnwrappingImageFilter()
{

  this->m_Laplacian = LaplacianType::New();
  this->m_Qual = QualType::New();
  this->m_DCT = DCTType::New();

  m_MaximumIterations = 100;
  m_MinimumEpsilon = 0.001;

}
 
template< class TImage>
void PCGPhaseUnwrappingImageFilter< TImage >
::GenerateData()
{

  typename TImage::ConstPointer input = this->GetInput();

  const unsigned int NUMPIX = input->GetLargestPossibleRegion().GetNumberOfPixels();

  typename TImage::Pointer output = this->GetOutput();
  this->AllocateOutputs();
  output->FillBuffer( 0 );
  
  // Allocate intermediate images
  typename TImage::Pointer zarray    = TImage::New();
  typename TImage::Pointer parray    = TImage::New();
  typename TImage::Pointer rarray    = TImage::New();
  typename TImage::Pointer soln      = TImage::New();
  typename TImage::Pointer qualImage = TImage::New();

  zarray->SetRegions( input->GetLargestPossibleRegion() );
  zarray->SetOrigin(  input->GetOrigin() );
  zarray->SetSpacing( input->GetSpacing() );
  zarray->Allocate();
  zarray->FillBuffer( 0 );

  parray->SetRegions( input->GetLargestPossibleRegion() );
  parray->SetOrigin(  input->GetOrigin() );
  parray->SetSpacing( input->GetSpacing() );
  parray->Allocate();
  parray->FillBuffer( 0 );

//  rarray->SetRegions( input->GetLargestPossibleRegion() );
//  rarray->SetOrigin(  input->GetOrigin() );
//  rarray->SetSpacing( input->GetSpacing() );
//  rarray->Allocate();
//  rarray->FillBuffer( 0 );

  soln->SetRegions( input->GetLargestPossibleRegion() );
  soln->SetOrigin(  input->GetOrigin() );
  soln->SetSpacing( input->GetSpacing() );
  soln->Allocate();
  soln->FillBuffer( 0 );

//  qualImage->SetRegions( input->GetLargestPossibleRegion() );
//  qualImage->SetOrigin(  input->GetOrigin() );
//  qualImage->SetSpacing( input->GetSpacing() );
//  qualImage->Allocate();
//  qualImage->FillBuffer( 0 );
 
  // Calculate Laplacian (aka rarray)
  m_Laplacian->SetInput( input );
//  m_Laplacian->SetWeight( LaplacianType::PhaseDerivativeVariance );
  m_Laplacian->SetWeighted(true);
  m_Laplacian->Update();
  rarray->Graft( m_Laplacian->GetOutput() );
//  rarray = m_Laplacian->GetOutput();
//  rarray->Update();


  ItType rIt( rarray, input->GetLargestPossibleRegion() );
  ItType zIt( zarray, input->GetLargestPossibleRegion() );
  ItType pIt( parray, input->GetLargestPossibleRegion() ); 
  
  double sum0 = 0;
  for (rIt.GoToBegin(); !rIt.IsAtEnd(); ++rIt)
    {
    sum0 += pow(rIt.Get(), 2);
    }

  sum0 = std::sqrt(sum0/NUMPIX);

  std::cout << "sum0: " << sum0 << std::endl;
 
  // Calculate quality
  m_Qual->SetInput( input );
  m_Qual->Update();
  qualImage->Graft( m_Qual->GetOutput() );
  qualImage->Update();

//  ImageAlgorithm::Copy(m_Qual->GetOutput(),
//                       qualImage.GetPointer(),
//                       qualImage->GetLargestPossibleRegion(),
//                       qualImage->GetLargestPossibleRegion());

  double beta, beta_previous, beta_temp;
  double alpha, epsilon, delta;
  
  for (unsigned int i = 0; i < m_MaximumIterations; ++i)
    {
    
    std::cout << "Iteration: " << i << " / " << m_MaximumIterations << std::endl;
 
    // Remove constant bias from rarray
    double bias = 0;
    for (rIt.GoToBegin(); !rIt.IsAtEnd(); ++rIt)
      {
      bias += rIt.Get();
      }

    bias /= NUMPIX;

    for (rIt.GoToBegin(); !rIt.IsAtEnd(); ++rIt)
      {
      rIt.Value() -= bias;
      }

    // Copy rarray into zarray
    ImageAlgorithm::Copy(rarray.GetPointer(),
                         zarray.GetPointer(),
                         zarray->GetLargestPossibleRegion(),
                         zarray->GetLargestPossibleRegion());

    
    // Compute cosine transform solution of Laplacian of zarray
    m_DCT->SetInput( zarray );
    m_DCT->Update();

    // Copy the solution into the transform into the zarray
    // Should DCTPhaseUnwrappingImageFilter inherit from InPlaceImageFilter?
    ImageAlgorithm::Copy(m_DCT->GetOutput(),
                         zarray.GetPointer(),
                         zarray->GetLargestPossibleRegion(),
                         zarray->GetLargestPossibleRegion());

    // Calculate beta
   
    beta = 0;
    for (rIt.GoToBegin(), zIt.GoToBegin(); !rIt.IsAtEnd(); ++rIt, ++zIt)
      {
      beta += rIt.Get()*zIt.Get();
      }

    std::cout << "Beta: " << beta << std::endl;
    
    // If this is the first iteration, copy zarray into parray
    if (0 == i)
      {
      ImageAlgorithm::Copy(zarray.GetPointer(),
                           parray.GetPointer(),
                           parray->GetLargestPossibleRegion(),
                           parray->GetLargestPossibleRegion());
      }
    else
      { // Otherwise, p = z + (beta/beta_previous) * p
    
      beta_temp = beta / beta_previous;
      
      for (pIt.GoToBegin(), zIt.GoToBegin(); !zIt.IsAtEnd(); ++pIt, ++zIt)
        {
        pIt.Set(zIt.Get() + beta_temp*pIt.Get());
        }

    }
    
    // Remove constant bias from parray   
    bias = 0;

    for (pIt.GoToBegin(); !pIt.IsAtEnd(); ++pIt)
      {
      bias += pIt.Get();
      }

    bias /= NUMPIX;

    for (pIt.GoToBegin(); !pIt.IsAtEnd(); ++pIt)
      {
      pIt.Value() -= bias;
      }

    // Assign beta to beta_previous
    beta_previous = beta;
 
    // Calculate Qp
    typename NItType::RadiusType radius;
    radius.Fill( 1 ); 
    
   // qualImage->FillBuffer( 1 );
    
    NItType pNIt( radius,
                  parray,
                  parray->GetLargestPossibleRegion() );

    NItType qualIt( radius,
                    m_Qual->GetOutput(), 
                    parray->GetLargestPossibleRegion() );
                    
    for (pNIt.GoToBegin(), qualIt.GoToBegin(), zIt.GoToBegin();
         !qualIt.IsAtEnd();
         ++qualIt, ++pNIt, ++zIt)
      {
    
      typename NItType::SizeValueType k = qualIt.Size() / 2;
      typename NItType::SizeValueType k1, k2;
      double w1, w2;
      double sumWeight = 0;
      
      zIt.Set( 0 );
    
      for (unsigned int d = 0; d < TImage::ImageDimension; ++d)
        {
      
        // Calculate offsets
        k1 = (qualIt.GetIndex()[d] < input->GetLargestPossibleRegion().GetSize()[d] - 1) ?
          k + qualIt.GetStride( d ) : k - qualIt.GetStride( d );
      
        k2 = (qualIt.GetIndex()[d] > 0) ? k - qualIt.GetStride( d ) : k + qualIt.GetStride( d );
        
        // Calculate weights
        w1 = qualIt.GetPixel( k1 );
        w2 = qualIt.GetPixel( k2 );
        
        double wCenter = qualIt.GetCenterPixel();
        w1 = (wCenter*wCenter < w1*w1) ? wCenter*wCenter : w1*w1;
        w2 = (wCenter*wCenter < w2*w2) ? wCenter*wCenter : w2*w2;
        
        sumWeight += (w1+w2);
        
        zIt.Value() -= w1*pNIt.GetPixel( k1 );
        zIt.Value() -= w2*pNIt.GetPixel( k2 );
      
        }
      
      zIt.Value() += sumWeight*pNIt.GetCenterPixel();
      
    
      }
    
    // Calculate alpha
    alpha = 0;

    for (zIt.GoToBegin(), pIt.GoToBegin(); !zIt.IsAtEnd(); ++zIt, ++pIt)
      {
      alpha += zIt.Get()*pIt.Get();
      }

    alpha = beta / alpha;

    std::cout << "Alpha: " << alpha << std::endl;

    // Update rarray
    for (rIt.GoToBegin(), zIt.GoToBegin(); !zIt.IsAtEnd(); ++rIt, ++zIt)
      {
      rIt.Value() -= alpha*zIt.Get();
      }

    // FIXME Book says 'update parray', but then modifies soln
    // FIXME Should solution be zeroed first?
    ItType sIt( soln, input->GetLargestPossibleRegion() );

    for (sIt.GoToBegin(), pIt.GoToBegin(); !sIt.IsAtEnd(); ++sIt, ++pIt)
      {
      sIt.Value() += alpha*pIt.Get();
      } 

    // Remove constant bias from SOLUTION
    bias = 0.0;

    for (sIt.GoToBegin(); !sIt.IsAtEnd(); ++sIt)
      {
      bias += sIt.Get();
      }

    bias /= NUMPIX;

    for (sIt.GoToBegin(); !sIt.IsAtEnd(); ++sIt)
      {
      sIt.Value() -= bias;
      }

    // Calculate EPSILON
    epsilon = 0.0;
    for (rIt.GoToBegin(); !rIt.IsAtEnd(); ++rIt)
      {
      epsilon += pow( rIt.Get(),2);
      }

    // FIXME: WHY ARE WE DIVIDING BIAS AGAIN??
    // FIXME: Should this be epsilon??
    epsilon = std::sqrt(epsilon/NUMPIX)/sum0;

    std::cout << "Epsilon: " << epsilon << std::endl;

    // Calculate DELTA
    delta = 0.0;
    for (pIt.GoToBegin(); !pIt.IsAtEnd(); ++pIt)
      {
      delta += pow(alpha, 2) * pow(pIt.Get(), 2);
      }

    delta = std::sqrt(delta/NUMPIX);
    std::cout << "Delta: " << delta << std::endl;

    std::cout << std::endl;
    
    // If epsilon falls below the threshold, break out.
    if (this->m_MinimumEpsilon >= epsilon) break;

  } 
 
  ImageAlgorithm::Copy(soln.GetPointer(),
                       output.GetPointer(),
                       output->GetLargestPossibleRegion(),
                       output->GetLargestPossibleRegion());
  
}

//  PrintSelf method prints parameters 

template < class TImage > 
void 
PCGPhaseUnwrappingImageFilter< TImage >::PrintSelf( std::ostream& os, Indent indent ) const 
{ 
  Superclass::PrintSelf(os,indent); 

  os 
    << indent << "No parameters." 
    << std::endl; 
} 
 
}// end namespace itk
 
#endif
