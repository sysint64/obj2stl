#include <benchmark/benchmark.h>

#include "obj.hpp"
#include "stl.hpp"
#include "utils.hpp"

void convert_to_stl(std::string const& file_name) {
    auto lines = utils::load_text_file_lines("../../tests/resources/" + file_name);
    auto obj = obj_file::load_from_string_lines(lines);
    auto layout = obj_file::create_mesh_layout_from_obj(obj);
    auto writer = std::make_unique<stl_file::StlMeshWriter>();
    writer->write(layout);
}

static void bm_bugatti(benchmark::State& state) {
  for (auto _ : state) {
      convert_to_stl("bugatti.obj");
  }
}

static void bm_complex(benchmark::State& state) {
  for (auto _ : state) {
      convert_to_stl("complex.obj");
  }
}

BENCHMARK(bm_bugatti);
BENCHMARK(bm_complex);

BENCHMARK_MAIN();
