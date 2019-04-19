cmake_minimum_required(VERSION 3.12)
project(Nibbler_v1.1)

add_custom_target(SDL_lib
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/SDL)
add_custom_target(SFML_lib
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/SFML)
add_custom_target(GL
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/GL)
add_custom_target(Music
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/Music)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Menu.cpp src/Game_Obj.cpp
                                           src/Logic.cpp
                                           src/Mmap.cpp
                                           src/Food.cpp
                                           src/Interface.cpp)
set(INC inc/)
set(INCLUDE_DIR ~/.brew/include/)
set(LIBRARY ~/.brew/lib/)


include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY})

include_directories(${INC})
link_directories(${INC})

message(STATUS "dir = '${CMAKE_CURRENT_SOURCE_DIR}'")

add_executable(Nibbler_v1.1 ${SOURCE_FILES})

target_link_libraries(Nibbler_v1.1 -rdynamic -ldl -lsfml-audio)