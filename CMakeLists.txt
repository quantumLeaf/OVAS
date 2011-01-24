PROJECT (VAS)
cmake_minimum_required(VERSION 2.6)



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


include_directories (${VAS_SOURCE_DIR})   


ADD_EXECUTABLE(testOVAS testOVAS.cpp Analyser4D.cpp abstractFeature.cpp  Feature.cpp      ImplicitVolume4D.cpp
Analyser3D.cpp       GeoPoint.cpp     StepToParamConverter.cpp
       GeoSequence.cpp  
       GeoSphere.cpp    Volume4D.cpp
) 
TARGET_LINK_LIBRARIES(testOVAS vtkWidgets vtkRendering vtkHybrid)
