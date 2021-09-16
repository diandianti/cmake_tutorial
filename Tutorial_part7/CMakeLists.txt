cmake_minimum_required(VERSION 3.10)

#set project name and version
project(Tutorial VERSION 1.0)

# add option
option(USE_MYMATH "Use tutorial provided math implementation" ON)
#########################################################################################

######################################### test config ###################################
#set config file
configure_file(TutorialConfig.h.in TutorialConfig.h)
add_executable(Tutorial Tutorial.cpp)
#this line must after add_executable, or will be error!
target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")
########################################################################################

######################################### test standard ################################
#set c++ standard
#if comment this line, the default compiler will be use
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(TestStd TestStd.cpp)
########################################################################################

# if USE_MYMATH is true 
if(USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
  message("USE_MYMATH is True")
endif()
########################################################################################

# tesr sqrt
add_executable(TestSqrt TestSqrt.cpp)

target_link_libraries(TestSqrt PUBLIC ${EXTRA_LIBS})

target_include_directories(TestSqrt PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
########################################################################################

# test test
add_executable(TestTest TestTest.cpp)
########################################################################################

# cmake test
enable_testing()

add_test(NAME Runs COMMAND TestTest 25)

add_test(NAME Usage COMMAND TestTest)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
  )

function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

do_test(TestTest 4 "2")
do_test(TestTest 9 "3")
do_test(TestTest 5 "2.236")
do_test(TestTest 7 "2.645")
do_test(TestTest 25 "5")
do_test(TestTest -25 "[-nan|nan|0]")
do_test(TestTest 0.0001 "0.01")
########################################################################################


# install 
install(TARGETS Tutorial DESTINATION bin)
install(TARGETS TestStd DESTINATION bin)
install(TARGETS TestSqrt DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  DESTINATION include
  )
########################################################################################


# pack files
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)
########################################################################################

