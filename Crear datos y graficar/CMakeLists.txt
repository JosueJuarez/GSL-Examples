project(Crear_datos_y_graficar)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(LIBS ${LIBS})
set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(main main.cpp)

find_package(GSL REQUIRED)

target_link_libraries(main  ${LIBS})
target_link_libraries(main  GSL::gsl GSL::gslcblas)
