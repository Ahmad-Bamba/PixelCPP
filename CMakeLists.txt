# cmake template for all homework
cmake_minimum_required(VERSION 3.12)

# project name and version
project(SpiteEngine VERSION 0.1)

# force c++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# src files
file(GLOB srcs "src/*.cpp")

# compile library
add_library(SpriteEngineLib SHARED ${srcs})
target_include_directories(SpriteEngineLib PUBLIC "include")

# compile test
add_executable(EngineTest "test.cpp" ${srcs})
# target_link_libraries(EngineTest PRIVATE SpriteEngineLib)
target_include_directories(EngineTest PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
