set(DOCUMENTATION "This module contains classes to manipulate
phase data.")

itk_module(ITKPhase
  DEPENDS
    ITKImageIntensity
    ITKCommon
    ITKFFT
    ITKThresholding
    ITKImageNoise
    ITKImageGradient
  TEST_DEPENDS
    ITKTestKernel
    ITKImageFeature
  DESCRIPTION
    "${DOCUMENTATION}"
)
