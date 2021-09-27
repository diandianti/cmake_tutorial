cmake_minimum_required(VERSION 3.10)

#set project name and version
project(Tutorial VERSION 1.0)

set(CMAKE_DEBUG_POSTFIX d)

# set static and shared libraries build path
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

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
add_executable(TestStd TestStd.cpp)

add_library(TestStd_compiler_flags INTERFACE)
target_compile_features(TestStd_compiler_flags INTERFACE cxx_std_11)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GUN>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(TestStd_compiler_flags INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformar=2;-Wunused>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
    )
########################################################################################

add_subdirectory(MathFunctions)

# tesr sqrt
add_executable(TestSqrt TestSqrt.cpp)

set_target_properties(TestSqrt PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(TestSqrt PUBLIC MathFunctions)

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
install(EXPORT MathFunctionsTargets
  FILE MathFunctionsTargets.cmake
  DESTINATION lib/cmake/MathFunctions
)
########################################################################################


# pack files
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)
########################################################################################


# export
install(EXPORT MathFunctionsTargets
  FILE MathFunctionsTargets.cmake
  DESTINATION lib/cmake/MathFunctions
)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/example"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake"
  VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

# install the configuration file
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
  DESTINATION lib/cmake/MathFunctions
  )
########################################################################################

