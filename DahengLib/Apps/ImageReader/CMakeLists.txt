FILE(GLOB src_files "*.*")

SET (ALL_SRCS ${src_files})

ADD_LIBRARY(ImageReader SHARED ${ALL_SRCS})

TARGET_LINK_LIBRARIES (ImageReader  CGVideo.lib CGVidEx.lib)

INSTALL_TARGETS (/bin ImageReader)