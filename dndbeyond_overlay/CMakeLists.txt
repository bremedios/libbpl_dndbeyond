cmake_minimum_required(VERSION 3.28)

project(dndbeyond_overlay)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL2_ttf)
find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

include_directories(${SDL_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ../libbpl_dndbeyond/include ../../libbpl_graphics/libbpl_graphics/include ../../libbpl_net/libbpl_net/include ../../libbpl_sys/libbpl_sys/include ../../libbpl_storage/libbpl_storage/include)
add_executable(dndbeyond_overlay src/dndbeyondapp.cpp src/OverlayUpdater.cpp
        src/Debug.h)

target_link_libraries(dndbeyond_overlay PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image bpl_net bpl_storage bpl_dndbeyond bpl_graphics)
