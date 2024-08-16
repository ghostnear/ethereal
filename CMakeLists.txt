cmake_minimum_required(VERSION 3.5)

project(ethereal)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE inc/ethereal
    PUBLIC inc
)

find_package(GLEW REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        GLEW::GLEW
)