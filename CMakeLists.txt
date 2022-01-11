cmake_minimum_required(VERSION 3.10)

set(APP GameOfLife)

project (${APP}
  VERSION 0.1.0
  LANGUAGES CXX C
)

find_package(gf REQUIRED COMPONENTS graphics)
find_package(Pomme REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT MSVC)
  add_definitions(-Wall -Wextra -g -pedantic)
endif()

add_executable(${APP}
  src/main.cpp
)

target_include_directories(${APP}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${APP}
  gf::graphics
  Pomme::Pomme
)

install(
  TARGETS ${APP}
  RUNTIME DESTINATION games
)