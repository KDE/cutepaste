cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Network)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Qt5Network_INCLUDE_DIRS}
)

set(cutepaste_SRCS main.cpp)
add_executable(cutepaste ${cutepaste_SRCS})
target_link_libraries(cutepaste Qt5::Network)

qt5_use_modules(cutepaste Network)
