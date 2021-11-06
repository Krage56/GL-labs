cmake_minimum_required(VERSION 3.17)
project(Gl-L2)

set(CMAKE_CXX_STANDARD 17)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
add_executable(Gl-L2 main.cpp)
target_link_libraries(Gl-L2 ${CONAN_LIBS})
