cmake_minimum_required(VERSION 3.26)
project(roguelight)

#for debugging
set(CMAKE_BUILD_TYPE Debug)

#for clang
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

set(SDL2_IMAGE_INCLUDE_DIRS "/usr/include/SDL2")
set(SDL2_IMAGE_LIBRARIES "/usr/lib/libSDL2_image.so")

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

#find src/*/*.cpp -type f
set(MY_SOURCES
    src/algorithms/fov.cpp
    src/algorithms/perlin.cpp
    src/animations/animation.cpp
    src/draw/draw_ui.cpp
    src/draw/tile_manager.cpp
    src/entities/ai.cpp
    src/entities/creature.cpp
    src/entities/entity.cpp
    src/entities/fighter.cpp
    src/entities/glow.cpp
    src/entities/item.cpp
    src/entities/monster_factory.cpp
    src/entities/player.cpp
    src/entities/tile.cpp
    src/entities/tile_factory.cpp
    src/inputManager/game_window.cpp
    src/inputManager/input_manager.cpp
    src/inputManager/inventory_window.cpp
    src/inputManager/menu_window.cpp
    src/particles/particle.cpp
    src/particles/particle_emitter.cpp
    src/procgen/levelgen.cpp
    src/colors.cpp
    src/game.cpp
    src/main.cpp
    src/map.cpp
)

message(STATUS "SDL2_image include dirs: ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2_image libraries: ${SDL2_IMAGE_LIBRARIES}")

add_executable(roguelight ${MY_SOURCES})

target_link_libraries(roguelight ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
