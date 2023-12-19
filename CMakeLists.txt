cmake_minimum_required(VERSION 3.27)

project(ferenc LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

add_executable(proba src/main.cc)

target_include_directories(proba PRIVATE include)

target_compile_options(proba PRIVATE -flto -Wall -Wextra -Wpedantic)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(proba PRIVATE -g -O0)
else()
  target_compile_options(proba PRIVATE -O3)
endif()
