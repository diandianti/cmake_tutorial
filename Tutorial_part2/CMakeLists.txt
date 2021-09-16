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
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
  message("USE_MYMATH is True")
endif()
########################################################################################

# tesr sqrt
add_executable(TestSqrt TestSqrt.cpp)

target_link_libraries(TestSqrt PUBLIC ${EXTRA_LIBS})

target_include_directories(TestSqrt PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ${EXTRA_INCLUDES}
                           )
########################################################################################


