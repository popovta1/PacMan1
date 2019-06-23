cmake_minimum_required(VERSION 3.7)
project(pac_man)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        game.cpp  game.h TextureManager.h TextureManager.cpp GameObject.h GameObject.cpp Ninja.h Ninja.cpp Map.h Map.cpp Grass.h Grass.cpp Map_object.h Map_object.cpp Sakura.h Sakura.cpp defs.h Pancake.h Pancake.cpp Samurai.h Samurai.cpp RedSamurai.h GreenSamurai.h YellowSamurai.h RedSamurai.cpp defs.cpp GreenSamurai.cpp YellowSamurai.cpp)

add_executable(pac_man ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
INCLUDE_DIRECTORIES(SDL2_ttf)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}  SDL2_ttf)
