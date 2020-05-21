# Shapr3D Home work

## Run

```
mkdir build && cd build
CXX=clang++ cmake ..
make -j<n> run
```

### CMAKE Options

- **ENABLE_CLANG_SANITIZE** - Enable clang sanitizer; *default*: ON;
- **ENABLE_TESTS** - Build tests and add `test` target; *default*: ON;
- **ENABLE_BENCHMARKING** - Build microbenchmarks and add `benchmark` target; *default*: ON;

## Run tests

```
make -j<n> && make test
```

To display test output with ctest

```
ctest --verbose
```

## Run benchmarks

```
make bench
```
