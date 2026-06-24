cmake_minimum_required(VERSION 4.0)
project(numa_task_runtime VERSION 1.0 LANGUAGES CXX)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Remove CMakeCache.txt and CMakeFiles.")
endif()

add_library(task_runtime STATIC src/init.cpp)
add_executable(benchmark benchmarks/test_bm.cpp)

target_compile_features(task_runtime PUBLIC cxx_std_20)
set_target_properties(task_runtime PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(task_runtime PUBLIC include/task_runtime/)

target_link_libraries(benchmark PRIVATE task_runtime)
