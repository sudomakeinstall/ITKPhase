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
 * =========================================================================*/
#ifndef itkIndexValuePair_h
#define itkIndexValuePair_h

namespace itk
{
/** \class IndexValuePair
 *  \ingroup ITKPhase
 * \brief A templated class containing an index-value pair, where equality is
 * determined based on index and < comparison is determined based on value.
 *
 * This class is intended to be used with the QualityGuidedPhaseUnwrappingImageFilter
 * class.
 *
 * TODO: Check that index supports == and that value supports <.
 *
 */
template < typename TIndex, typename TValue >
class IndexValuePair
{

public:

  void SetIndex(TIndex index)
    {
    this->m_Index = index;
    }
  TIndex GetIndex() const
    {
    return this->m_Index;
    }

  void SetValue(TValue value)
    {
    this->m_Value = value;
    }
  TValue GetValue() const
    {
    return this->m_Value;
    }

  /** Compare two points for equality. */
  bool
  operator==(const IndexValuePair & pt) const
  {
    return this->m_Index == pt.GetIndex();
  }

  /** Less than. */
  bool
  operator<(const IndexValuePair & pt) const
  {
    return this->m_Value < pt.GetValue();
  }

private:

  TIndex m_Index;
  TValue m_Value;

};

}

#endif
