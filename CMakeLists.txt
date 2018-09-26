cmake_minimum_required(VERSION 3.12)
project(DestructibleGround)

set(CMAKE_CXX_STANDARD 14)


add_executable(DestructibleGround main.cpp main.h Ground.cpp Ground.h main.h bomb.cpp bomb.h)

file(COPY assets DESTINATION ./)

include_directories("/usr/local/includes/SFML")
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} "/usr/local/Frameworks/freetype.framework/Versions/A/freetype")

