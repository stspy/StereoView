FILE(GLOB src_files "*.*")

SET (ALL_SRCS ${src_files})

ADD_LIBRARY(DahengImageCapture SHARED ${ALL_SRCS})

TARGET_LINK_LIBRARIES (DahengImageCapture  ${OpenCV_LIBS} ImageReader)

INSTALL_TARGETS (/lib DahengImageCapture)

INSTALL (FILES ${ALL_INCLUDES} DESTINATION include)