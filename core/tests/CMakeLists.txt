cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
include(CutePasteMacros)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CUTEPASTE_CORE_INCLUDE_DIRS}
)

set(CUTEPASTE_CORE_TEST_LIBRARIES ${CUTEPASTE_CORE_LIBRARIES} ${Qt5Test_LIBRARIES})

CUTEPASTE_UNIT_TESTS(
    "${CUTEPASTE_CORE_TEST_LIBRARIES}"
    "cutepastecore"

    # Source files without the extension
    # dictionaryinfotest
)
