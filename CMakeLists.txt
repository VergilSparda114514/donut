cmake_minimum_required(VERSION 3.20)
project(donut VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_subdirectory(vendor/FTXUI)
add_subdirectory(vendor/glm)

include_directories(
    vendor/FTXUI/include
    vendor/glm
)

file(GLOB_RECURSE PROJECT_SOURCE CONFIGURE_DEPENDENT ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCE})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ftxui glm)