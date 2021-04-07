cmake_minimum_required(VERSION 3.8.0)
project(zbs)

set(Torch_DIR /home/zbs/anaconda3/envs/AlphaZero/lib/python3.7/site-packages/torch/share/cmake/Torch)
find_package(Torch REQUIRED)
find_package(SWIG REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++14 -pthread -O3")

include_directories(${PROJECT_SOURCE_DIR}/src)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
add_executable(zbs ${DIR_SRCS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

target_link_libraries(zbs "${TORCH_LIBRARIES}")