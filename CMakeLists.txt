cmake_minimum_required(VERSION 3.12)
project(Nibbler_v1.1)

add_custom_target(SDL_lib
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/SDL)
add_custom_target(SFML_lib
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/SFML)
add_custom_target(GL
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/GL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Menu.cpp Game_Obj.cpp Logic.cpp Mmap.cpp AView.cpp Food.cpp Interface.cpp Interface.hpp Music.hpp)
set(INCLUDE_DIR ~/.brew/include/)
set(LIBRARY ~/.brew/lib/)


include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY})

message(STATUS "dir = '${CMAKE_CURRENT_SOURCE_DIR}'")

add_executable(Nibbler_v1.1 ${SOURCE_FILES})

target_link_libraries(Nibbler_v1.1 -rdynamic -ldl -lsfml-audio)