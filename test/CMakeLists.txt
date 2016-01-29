itk_module_test()

Set(ITK${itk-module}Tests
  itkDCTImageFilterTest.cxx
  itkDCTPhaseUnwrappingImageFilterTest.cxx
#  itkHelmholtzDecompositionImageFilterTest.cxx
  itkIndexValuePairTest.cxx
  itkItohPhaseUnwrappingImageFilterTest.cxx
  itkDCTPoissonSolverImageFilterTest.cxx
  itkPhaseDerivativeVarianceImageFilterTest.cxx
  itkPhaseExamplesImageSourceTest.cxx
#  itkPhaseImageToImageFilterTest.cxx
  itkPhaseQualityImageFilterTest.cxx
  itkPhaseResidueImageFilterTest.cxx
  itkQualityGuidedPhaseUnwrappingImageFilterTest.cxx
#  itkWrappedPhaseDifferencesBaseImageFilterTest.cxx
  itkWrappedPhaseLaplacianImageFilterTest.cxx
  itkWrapPhaseFunctorTest.cxx
  itkWrapPhaseImageFilterTest.cxx
)

CreateTestDriver(${itk-module}  "${${itk-module}-Test_LIBRARIES}" "${ITK${itk-module}Tests}")

itk_add_test(NAME itkDCTImageFilterTest
  COMMAND ${itk-module}TestDriver itkDCTImageFilterTest )
itk_add_test(NAME itkDCTPhaseUnwrappingImageFilterTest
  COMMAND ${itk-module}TestDriver itkDCTPhaseUnwrappingImageFilterTest
    DATA{Input//swi_wrapped.vtk} DATA{Input//swi_unwrapped_dct.vtk} )
itk_add_test(NAME itkIndexValuePairTest
  COMMAND ${itk-module}TestDriver itkIndexValuePairTest )
itk_add_test(NAME itkItohPhaseUnwrappingImageFilterTest
  COMMAND ${itk-module}TestDriver itkItohPhaseUnwrappingImageFilterTest )
itk_add_test(NAME itkDCTPoissonSolverImageFilterTest
  COMMAND ${itk-module}TestDriver itkDCTPoissonSolverImageFilterTest
    DATA{${ITK_DATA_ROOT}/Input/CellsFluorescence1.png} )
itk_add_test(NAME itkPhaseDerivativeVarianceImageFilterTest
  COMMAND ${itk-module}TestDriver itkPhaseDerivativeVarianceImageFilterTest )
itk_add_test(NAME itkPhaseExamplesImageSourceTest
  COMMAND ${itk-module}TestDriver itkPhaseExamplesImageSourceTest )
itk_add_test(NAME itkPhaseQualityImageFilterTest
  COMMAND ${itk-module}TestDriver itkPhaseQualityImageFilterTest )
itk_add_test(NAME itkPhaseResidueImageFilterTest
  COMMAND ${itk-module}TestDriver itkPhaseResidueImageFilterTest )
itk_add_test(NAME itkWrappedPhaseLaplacianImageFilterTest
  COMMAND ${itk-module}TestDriver itkWrappedPhaseLaplacianImageFilterTest )
itk_add_test(NAME itkWrapPhaseFunctorTest
  COMMAND ${itk-module}TestDriver itkWrapPhaseFunctorTest )
