cmake_minimum_required(VERSION 3.12)
project(DestructibleGround)

set(CMAKE_CXX_STANDARD 14)


add_executable(DestructibleGround main.cpp Ground.cpp Ground.h)

include_directories("/usr/local/include/SFML")
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} "/usr/local/Frameworks/freetype.framework/Versions/A/freetype")