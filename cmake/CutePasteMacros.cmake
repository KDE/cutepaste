# This file contains macros that are used inside the CurlPaste Project

MACRO(CURLPASTE_UNIT_TESTS libraries modulename)
    FOREACH(testname ${ARGN})
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${libraries} ${QT_QTTEST_LIBRARY})
        add_test("${modulename}-${testname}" ${modulename}-${testname})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(CURLPASTE_UNIT_TESTS)

MACRO(CURLPASTE_EXECUTABLE_TESTS libraries modulename1)
    FOREACH(testname ${ARGN})
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${libraries} ${QT_QTTEST_LIBRARY})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(CURLPASTE_EXECUTABLE_TESTS)

