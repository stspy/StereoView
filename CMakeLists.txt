cmake_minimum_required(VERSION 2.6)
#
# Set the project name.
#

PROJECT (StereoView)

SET (EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL
  "Where to put the executables")

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib CACHE INTERNAL
  "Where to put the libraries")

SET (DEBUG 1)



SUBDIRS ( 
  DahengLib 
  StereoInfo
  )




FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/DahengLib/Apps/ImageReader)
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/DahengLib/Apps/DahengImageCapture)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})




 
  
