INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_UHDUTILS uhdutils)

FIND_PATH(
    UHDUTILS_INCLUDE_DIRS
    NAMES uhdutils/api.h
    HINTS $ENV{UHDUTILS_DIR}/include
        ${PC_UHDUTILS_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    UHDUTILS_LIBRARIES
    NAMES gnuradio-uhdutils
    HINTS $ENV{UHDUTILS_DIR}/lib
        ${PC_UHDUTILS_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(UHDUTILS DEFAULT_MSG UHDUTILS_LIBRARIES UHDUTILS_INCLUDE_DIRS)
MARK_AS_ADVANCED(UHDUTILS_LIBRARIES UHDUTILS_INCLUDE_DIRS)

