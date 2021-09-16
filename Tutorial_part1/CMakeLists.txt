cmake_minimum_required(VERSION 3.10)

#set project name and version
project(Tutorial VERSION 1.0)

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


