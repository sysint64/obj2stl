include(GoogleTest)

find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

set(SOURCE_FILES ../src/obj.cpp
  ../src/utils.cpp
  ../src/mesh.cpp
  ../src/triangulation.cpp
  ../src/mesh_layout_reader.cpp
  ../src/stl.cpp
  ../src/format.cpp
  ../src/bytes_writer.cpp
  ../src/calc.cpp)

macro(add_simple_test name)
  add_executable(${name} "${SOURCE_FILES};${name}.cpp")
  target_link_libraries(${name} ${GTEST_LIBRARY})
  gtest_add_tests(TARGET ${name})
endmacro(add_simple_test)

add_simple_test(obj)
add_simple_test(mesh)
add_simple_test(triangulation)
add_simple_test(mesh_layout_reader)
add_simple_test(stl)
add_simple_test(bytes_writer)
add_simple_test(calc)
