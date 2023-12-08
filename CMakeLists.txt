cmake_minimum_required(VERSION 3.12)
project(KnightTour)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(KnightTour src/CheckerBoard.cpp src/Knight.cpp main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(COPY ${CMAKE_SOURCE_DIR}/media DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(KnightTour PRIVATE sfml-graphics sfml-window sfml-system)
