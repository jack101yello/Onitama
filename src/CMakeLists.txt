cmake_minimum_required(VERSION 3.16.3)

project(Onitama)
add_definitions("-Wall" "-Wextra" "-g")
file(GLOB_RECURSE SRCS *.cpp *.h src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${SRCS})
