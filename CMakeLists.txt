cmake_minimum_required(VERSION 3.0.0)
project(TerminalSuDoKu VERSION 1.0)

add_compile_options(
  # c++ version:
  # -----------
  -std=c++2a

  # compiler warnings:
  # ----------
  -Wall
  -Wextra
  -Wpedantic
  -Werror

  # optimization/debugging level:
  # ----------------------------
  -g
  # -O1
  # -O2
  # -O3
)


include_directories(
  src
  media
  boards
)

add_executable(
  TerminalSuDoKu
  src/main.cpp
  src/sudoku.cpp
  src/game.cpp
  )

# locate& link external library (fmt)
find_package(fmt)

target_link_libraries(
  TerminalSuDoKu fmt::fmt
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
