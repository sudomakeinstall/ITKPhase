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
#ifndef itkIntegralImageFilter_h
#define itkIntegralImageFilter_h 

#include "itkImageToImageFilter.h"
#include "itkImageLinearIteratorWithIndex.h"

namespace itk {

template < typename TInputImage, typename TOutputImage > 
class IntegralImageFilter: 
public ImageToImageFilter< TInputImage, TOutputImage > 
{ 
public: 

  //  Standard declarations 
  //  Used for object creation with the object factory: 
  typedef IntegralImageFilter                         Self; 
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass; 
  typedef SmartPointer< Self >                            Pointer; 
  typedef SmartPointer< const Self >                      ConstPointer; 

  /** Method for creation through object factory */
  itkNewMacro(Self);

  /** Run-time type information */
  itkTypeMacro(IntegralImageFilter, ImageToImageFilter);

  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const ITK_OVERRIDE;

protected: 

  IntegralImageFilter(){};
  ~IntegralImageFilter(){}

  //  Declare the component filter types:
  typedef ImageLinearIteratorWithIndex< TInputImage > ItType;
        
  void SumSingleDimension( unsigned int i, ItType it );
  void GenerateData() ITK_OVERRIDE;

private: 

  ITK_DISALLOW_COPY_AND_ASSIGN(IntegralImageFilter);

}; 

}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkIntegralImageFilter.hxx"
#endif

#endif // __itkIntegralImageFilter_h
