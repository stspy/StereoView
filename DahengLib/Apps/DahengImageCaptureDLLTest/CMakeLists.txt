FILE(GLOB src_files "*.*")


SET (ALL_SRCS ${src_files})


ADD_EXECUTABLE (DahengImageCaptureDLLTest ${ALL_SRCS})


TARGET_LINK_LIBRARIES (DahengImageCaptureDLLTest ${OpenCV_LIBS} DahengImageCapture)



INSTALL_TARGETS (/bin DahengImageCaptureDLLTest)