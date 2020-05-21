find_package(benchmark REQUIRED)

set(OUTS)

macro(add_benchmark name)
  add_executable(${name} "${name}.cpp")
  target_link_libraries(${name} benchmark::benchmark)
  list(APPEND OUTS "${name}.out")
  add_custom_command(OUTPUT ${name}.out COMMAND ${name})
endmacro(add_benchmark)

add_benchmark(sample_bench)
add_benchmark(sample_bench2)

message("${COMMANDS}")
add_custom_target(bench DEPENDS ${OUTS})
