include(GoogleTest)

find_package(GTest REQUIRED)
# find_package(GMock REQUIRED)

set(SOURCE_FILES ../src/obj.cpp ../src/utils.cpp ../src/mesh.cpp)

macro(add_simple_test name)
  add_executable(${name} "${SOURCE_FILES};${name}.cpp")
  target_link_libraries(${name} ${GTEST_LIBRARY})
  gtest_add_tests(TARGET ${name})
endmacro(add_simple_test)

add_simple_test(obj)
add_simple_test(mesh)
