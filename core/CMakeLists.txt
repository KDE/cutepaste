cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

set(BIN_INSTALL_DIR         bin                 CACHE INTERNAL  "The subdirectory relative to the install prefix where binary files will be installed.")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cutepaste_global.h.in ${CMAKE_CURRENT_BINARY_DIR}/cutepaste_global.h)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CUTEPASTE_CORE_INCLUDE_DIRS
    ${Qt5Core_INCLUDE_DIRS}
    CACHE PATHS "Includes required for CutePaste Core"
)

# set(CutePasteCore_SRCS
#     foo.cpp
# )

# set(CutePasteCore_HEADERS
#     cutepaste_core_export.h
# 	${CMAKE_CURRENT_BINARY_DIR}/cutepaste_global.h
# )

# add_library(CutePasteCore SHARED ${CutePasteCore_SRCS})

# qt5_use_modules(CutePasteCore Core)

# set(CUTEPASTE_CORE_LIBRARIES
#     CutePasteCore
#     ${Qt5Core_LIBRARIES}
#     CACHE PATHS "Libraries required for CutePaste Core"
# )

# if(BUILD_CUTEPASTE_TESTS)
#     enable_testing()
#     add_subdirectory(tests)
# endif()
