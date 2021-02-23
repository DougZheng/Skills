cmake_minimum_required(VERSION 3.8.0)
project(zbs)

set(Torch_DIR /usr/local/libtorch/share/cmake/Torch)
find_package(Torch REQUIRED)

add_executable(zbs zbs.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

target_link_libraries(zbs "${TORCH_LIBRARIES}")
# set_property(TARGET zbs PROPERTY CXX_STANDARD 11)