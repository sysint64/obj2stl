cmake_minimum_required(VERSION 3.9)
project(shapr3d_homework)

option(ENABLE_CLANG_SANITIZE "ENABLE_CLANG_SANITIZE" ON)
option(ENABLE_TESTS "Enable tests" ON)
option(ENABLE_BENCHMARKING "Enable benchmarking" ON)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(DEBUG_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0")

if (APPLE)
  set(CMAKE_CXX_FLAGS "${DEBUG_FLAGS} -std=c++17 -stdlib=libc++")

  # TODO: remove hardcode
  include_directories(~/Documents/libcxx/include)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_FLAGS} -std=c++17")
endif()

if (ENABLE_CLANG_SANITIZE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined")
  set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(GLM REQUIRED)

add_definitions(-DGLM_FORCE_RADIANS)

set(SOURCE_FILES src/obj.cpp
  src/utils.cpp
  src/mesh.cpp
  src/triangulation.cpp)

add_executable(main src/main.cpp ${SOURCE_FILES})
include_directories(include/)

if (ENABLE_BENCHMARKING)
  add_subdirectory(benchmarks)
endif()

if (ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

target_link_libraries(main ${LIBS})
add_custom_target(run COMMAND main)
