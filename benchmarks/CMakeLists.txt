find_package(benchmark REQUIRED)

set(OUTS)

set(SOURCE_FILES ../src/obj.cpp
  ../src/utils.cpp
  ../src/mesh.cpp
  ../src/triangulation.cpp
  ../src/mesh_layout_reader.cpp
  ../src/stl.cpp
  ../src/format.cpp
  ../src/bytes_writer.cpp
  ../src/calc.cpp)

set(CMAKE_CXX_FLAGS "-O3 -std=c++17")
set(CMAKE_LINKER_FLAGS "-fno-omit-frame-pointer -mno-omit-leaf-frame-pointer")
unset(CMAKE_CXX_CLANG_TIDY)

macro(add_benchmark name)
  add_executable(${name}_bench "${SOURCE_FILES};${name}.cpp")
  target_link_libraries(${name}_bench benchmark::benchmark)
  list(APPEND OUTS "${name}_bench.out")
  add_custom_command(OUTPUT ${name}_bench.out COMMAND ${name}_bench)
endmacro(add_benchmark)

add_benchmark(stl)

add_custom_target(bench DEPENDS ${OUTS})
