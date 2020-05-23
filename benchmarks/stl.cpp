#include <benchmark/benchmark.h>

#include "obj.hpp"
#include "stl.hpp"
#include "utils.hpp"
#include "calc.hpp"

std::shared_ptr<mesh::MeshLayout> load_layout(std::string const& file_name) {
    auto lines = utils::load_text_file_lines("../../tests/resources/" + file_name);
    auto obj = obj_file::load_from_string_lines(lines);
    return obj_file::create_mesh_layout_from_obj(obj);
}

static auto box = load_layout("box.obj");
static auto complex = load_layout("complex.obj");
static auto bugatti = load_layout("bugatti.obj");

void convert_to_stl(std::shared_ptr<mesh::MeshLayout> const& layout) {
    auto writer = std::make_unique<stl_file::StlMeshWriter>();
    writer->write(layout);
}

void apply_transforms(std::shared_ptr<mesh::MeshLayout> const& layout) {
    calc::apply_transforms_to_layout(
        layout,
        glm::vec3(123, 93, 56),
        glm::vec3(34, 91, 43),
        glm::vec3(12, 33, 10)
    );
}

static void bm_load_layout_box(benchmark::State& state) {
    for (auto _ : state) {
        load_layout("box.obj");
    }
}

static void bm_load_layout_complex(benchmark::State& state) {
    for (auto _ : state) {
        load_layout("complex.obj");
    }
}

static void bm_load_layout_bugatti(benchmark::State& state) {
    for (auto _ : state) {
        load_layout("bugatti.obj");
    }
}

static void bm_convert_to_stl_box(benchmark::State& state) {
    for (auto _ : state) {
        convert_to_stl(box);
    }
}

static void bm_convert_to_stl_complex(benchmark::State& state) {
    for (auto _ : state) {
        convert_to_stl(complex);
    }
}

static void bm_convert_to_stl_bugatti(benchmark::State& state) {
    for (auto _ : state) {
        convert_to_stl(bugatti);
    }
}

static void bm_apply_transforms_box(benchmark::State& state) {
    for (auto _ : state) {
        apply_transforms(box);
    }
}

static void bm_apply_transforms_complex(benchmark::State& state) {
    for (auto _ : state) {
        apply_transforms(complex);
    }
}

static void bm_apply_transforms_bugatti(benchmark::State& state) {
    for (auto _ : state) {
        apply_transforms(bugatti);
    }
}

static void bm_calculate_surface_area_box(benchmark::State& state) {
    for (auto _ : state) {
        calc::calculate_surface_area(box);
    }
}

static void bm_calculate_surface_area_complex(benchmark::State& state) {
    for (auto _ : state) {
        calc::calculate_surface_area(complex);
    }
}

static void bm_calculate_surface_area_bugatti(benchmark::State& state) {
    for (auto _ : state) {
        calc::calculate_surface_area(bugatti);
    }
}

static void bm_calculate_volume_box(benchmark::State& state) {
    for (auto _ : state) {
        calc::calculate_volume(box);
    }
}

static void bm_calculate_volume_complex(benchmark::State& state) {
    for (auto _ : state) {
        calc::calculate_volume(complex);
    }
}

static void bm_calculate_volume_bugatti(benchmark::State& state) {
    for (auto _ : state) {
        calc::calculate_volume(bugatti);
    }
}

static void bm_is_point_inside_mesh_box(benchmark::State& state) {
    for (auto _ : state) {
        calc::is_point_inside_mesh(glm::vec3(12, 11, 0), box);
    }
}

static void bm_is_point_inside_mesh_complex(benchmark::State& state) {
    for (auto _ : state) {
        calc::is_point_inside_mesh(glm::vec3(12, 11, 0), complex);
    }
}

static void bm_is_point_inside_mesh_bugatti(benchmark::State& state) {
    for (auto _ : state) {
        calc::is_point_inside_mesh(glm::vec3(12, 11, 0), bugatti);
    }
}

BENCHMARK(bm_load_layout_box);
BENCHMARK(bm_load_layout_complex);
BENCHMARK(bm_load_layout_bugatti);

BENCHMARK(bm_convert_to_stl_box);
BENCHMARK(bm_convert_to_stl_complex);
BENCHMARK(bm_convert_to_stl_bugatti);

BENCHMARK(bm_apply_transforms_box);
BENCHMARK(bm_apply_transforms_complex);
BENCHMARK(bm_apply_transforms_bugatti);

BENCHMARK(bm_calculate_surface_area_box);
BENCHMARK(bm_calculate_surface_area_complex);
BENCHMARK(bm_calculate_surface_area_bugatti);

BENCHMARK(bm_calculate_volume_box);
BENCHMARK(bm_calculate_volume_complex);
BENCHMARK(bm_calculate_volume_bugatti);

BENCHMARK(bm_is_point_inside_mesh_box);
BENCHMARK(bm_is_point_inside_mesh_complex);
BENCHMARK(bm_is_point_inside_mesh_bugatti);


BENCHMARK_MAIN();
