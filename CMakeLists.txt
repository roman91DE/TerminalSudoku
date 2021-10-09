cmake_minimum_required(VERSION 3.0.0)
project(CL_Sudoku VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CL_Sudoku main.cpp)

find_package(fmt)

target_link_libraries(
  CL_Sudoku fmt::fmt
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
