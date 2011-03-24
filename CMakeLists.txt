PROJECT (OVAS)
cmake_minimum_required(VERSION 2.6)

FIND_PACKAGE(VXL)


FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})

#FIND_PACKAGE(ITK)
#IF(ITK_FOUND)
#INCLUDE(${ITK_USE_FILE})
#ELSE(ITK_FOUND)
#MESSAGE(FATAL_ERROR
#"ITK not found. Please set ITK_DIR.")
#ENDIF(ITK_FOUND)


#include_directories (${VAS_SOURCE_DIR})   

include_directories (${VAS_SOURCE_DIR} "/usr/local/include/vxl/core/" "/usr/local/include/vxl/vcl/")


ADD_EXECUTABLE(testOVAS testOVAS.cpp Analyser4D.cpp abstractFeature.cpp  Feature.cpp ImplicitVolume4D.cpp
Analyser3D.cpp GeoPoint.cpp StepToParamConverter.cpp
       GeoSequence.cpp GeoSphere.cpp    Volume4D.cpp MetaballsVol4D FeatureWeights.cpp ViewEvaluator.cpp testVol4D.cpp OVASControl.cpp FrameBuffer.cpp TemporalChangeFeature.cpp arraytools.h AreaFeature.cpp InfoSheet.cpp InfoData.cpp FlyingSaucersVol4D.cpp PathVisualiser.cpp TemporalChangeFeature2.cpp MovingAAElipsoid.cpp
) 
TARGET_LINK_LIBRARIES(testOVAS vtkWidgets vtkRendering vtkHybrid vnl)
