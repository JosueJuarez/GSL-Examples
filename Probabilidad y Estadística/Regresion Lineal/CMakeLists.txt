project(Regresion_Lineal)

cmake_minimum_required(VERSION 3.23.1 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(LIBS ${LIBS})
set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(main main.cpp)

find_package(GSL REQUIRED)

target_link_libraries(main  ${LIBS})
target_link_libraries(main  GSL::gsl GSL::gslcblas)
