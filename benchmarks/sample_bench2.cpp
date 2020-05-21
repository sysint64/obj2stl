#include <stdio.h>
#include <benchmark/benchmark.h>

int sum(int a, int b) {
    return a + b;
}

static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
      sum(1, 2);
  }
}

// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);

// Run the benchmark
BENCHMARK_MAIN();
