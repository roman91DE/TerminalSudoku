cmake_minimum_required(VERSION 3.0.0)
project(TerminalSuDoKu VERSION 1.0)

add_compile_options(
  -std=c++17       # macOS
  #-std=gnu++17      # ubuntu
  # set compiler warnings to maximum
  -Wall
  -Wextra
  -Wpedantic
  -Werror
)

# include(CTest)
# enable_testing()

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

# locate fmt library
find_package(fmt)
# link project to fmt
target_link_libraries(
  TerminalSuDoKu fmt::fmt
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
