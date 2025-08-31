cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(snake)
include("${VITASDK}/share/vita.cmake" REQUIRED)

find_package(SDL2 REQUIRED)

set(VITA_APP_NAME "Snake")
set(VITA_TITLEID "VSDK00017")
set(VITA_VERSION "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(includes)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/game.cpp
  src/player.cpp
  src/game_obj.cpp
  src/tile_map.cpp
  src/tail_node.cpp
  src/audio.cpp
  )

target_link_libraries(${PROJECT_NAME}
  SDL2_mixer
  SDL2::SDL2
  SDL2_image
  png
  png16
  jpeg
  z
  webp
  webpdemux
  opusfile
  opus
  stdc++
  pthread

  xmp
  mikmod
  mpg123
  FLAC
  modplug
  vorbisfile
  vorbis
  ogg
  m
  )

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml

  FILE resources/audio/snake.ogg resources/audio/snake.ogg
  FILE resources/images/grass.png resources/images/grass.png
  FILE resources/images/snake_head.png resources/images/snake_head.png
  FILE resources/images/snake_body.png resources/images/snake_body.png
  )
