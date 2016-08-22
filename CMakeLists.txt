CMAKE_MINIMUM_REQUIRED(VERSION 2.8)#设定版本
PROJECT(space_time)#设定工程名
#SET(CMAKE_CXX_COMPLIER "g++")#设定编译器

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#SET(CMAKE_CXX_FLAGS "-O3 -fPIC -std=c++0x")
#For annotated profiling with perf: 
#SET(CMAKE_CXX_FLAGS "-ggdb -O3 -fPIC -std=c++0x")
SET(CMAKE_CXX_FLAGS "-ggdb -O3 -fPIC")

#############################
# OpenCV ####################
#############################

find_package(OpenCV REQUIRED) 
message("OpenCV_LIBS = ${OpenCV_LIBS}") 
#include_directories(${OpenCV_INCLUDE_DIRS})
#link_directories(${OpenCV_LIBRARY_DIRS})

# g2o #######################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules/")
#message(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})
find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIRS})
link_directories(${G2O_LIBRARY_DIRS})
link_libraries(${G2O_LIBRARIES})
message("G2o-libraries " ${G2O_LIBRARIES})

#############################
# Eigen ####################
#############################
find_package(Eigen)
include_directories(${EIGEN_INCLUDE_DIRS})
add_definitions(${EIGEN_DEFINITIONS})

include_directories(external/ /usr/include/suitesparse/)
#####################################
# Sources to Compile
#####################################
SET(ADDITIONAL_SOURCES src/main.cpp src/keyslice_tracker.cpp )

####################################
# Binaries
###################################
#add_executable(slam  ${ADDITIONAL_SOURCES} ${QT_MOC_HPP})
add_executable(space_time  ${ADDITIONAL_SOURCES})

SET(LIBS_LINK  ${OpenCV_LIBS} ${G2O_LIBRARIES} )
target_link_libraries(space_time ${LIBS_LINK}  )
