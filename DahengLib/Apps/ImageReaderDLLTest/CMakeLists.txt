FILE(GLOB src_files "*.*")


SET (ALL_SRCS ${src_files})


ADD_EXECUTABLE (ImageReaderDLLTest ${ALL_SRCS})


TARGET_LINK_LIBRARIES (ImageReaderDLLTest ${OpenCV_LIBS} ImageReader)



INSTALL_TARGETS (/bin ImageReaderDLLTest)