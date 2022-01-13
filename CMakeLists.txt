cmake_minimum_required(VERSION 3.10)

set(GAME GameOfLife)

project (${GAME}
  VERSION 0.1.0
  LANGUAGES CXX C
)

include(GNUInstallDirs)

find_package(gf REQUIRED COMPONENTS graphics)
find_package(Pomme REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif ()

set(GAME_DATADIR "${CMAKE_INSTALL_PREFIX}/share/games/${GAME}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

add_executable(${GAME}
  src/main.cpp
  src/bits/GameHub.cpp
  src/bits/GameScene.cpp
)

target_include_directories(${GAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${GAME}
  gf::graphics
  Pomme::Pomme
)

install(
  TARGETS ${GAME}
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/${GAME}"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)