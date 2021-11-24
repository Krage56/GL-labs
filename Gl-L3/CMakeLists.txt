cmake_minimum_required(VERSION 3.17)
project(Gl-L3)

set(CMAKE_CXX_STANDARD 17)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
add_executable(Gl-L3 main.cpp)
target_link_libraries(Gl-L3 ${CONAN_LIBS})
