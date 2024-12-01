cmake_minimum_required(VERSION 3.25)

project(bpl_dndbeyond)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL2_TTF)
find_package(SDL2_IMAGE REQUIRED CONFIG COMPONENTS SDL2_image)

include_directories(include)

set(PUBLIC_HEADER include/bpl/dndbeyond/api/Class.h
        include/bpl/dndbeyond/api/Classes.h
        include/bpl/dndbeyond/api/Data.h
        include/bpl/dndbeyond/api/Decorations.h
        include/bpl/dndbeyond/api/Inventory.h
        include/bpl/dndbeyond/api/InventoryItem.h
        include/bpl/dndbeyond/api/InventoryItemDefinition.h
        include/bpl/dndbeyond/api/Response.h
        include/bpl/dndbeyond/api/Stats.h
        include/bpl/dndbeyond/Api.h
        include/bpl/dndbeyond/CharacterData.h)
set(SOURCE_FILES src/Api.cpp
        src/CharacterData.cpp
        src/api/Class.cpp
        src/api/Classes.cpp
        src/api/Data.cpp
        src/api/Decorations.cpp
        src/api/Inventory.cpp
        src/api/InventoryItem.cpp
        src/api/InventoryItemDefinition.cpp
        src/api/Response.cpp
        src/api/Stats.cpp)

add_library(bpl_dndbeyond SHARED ${SOURCE_FILES} ${PUBLIC_HEADER} )
target_link_libraries(bpl_dndbeyond PRIVATE )

install(TARGETS bpl_dndbeyond DESTINATION lib)
install(FILES include/bpl/dndbeyond/Window.h DESTINATION include/bpl/net)
install(FILES include/bpl/dndbeyond/Renderer.h DESTINATION include/bpl/net)