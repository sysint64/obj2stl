# Shapr3D Home work

## Compile

```
mkdir build && cd build
CXX=clang++ cmake ..
make -j<n>
```

### CMAKE Options

- **ENABLE_CLANG_SANITIZE** - Enable clang sanitizer; *default*: ON;
- **ENABLE_TESTS** - Build tests and add `test` target; *default*: ON;
- **ENABLE_BENCHMARKING** - Build microbenchmarks and add `bench` target; *default*: ON;

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

## Usage

### Show help

```
./main --help
```

### Convert from obj to stl

```
./main -c -i "<obj-file-path>" -o "<stl-file-path>"
```

### Apply some transformations:

```
./main -c -i "<obj-file-path>" -o "<stl-file-path>" --ty 2 --tz 3 --rx 45 --ry 45 --sx 2 --sz 5
```

### Calculate surface area

```
./main -s -i "<obj-file-path>"
```

### Calculate volume (experimental)

```
./main -v -i "<obj-file-path>"
```

### Test whether point inside 3d mesh (experimental)

```
./main -p -i "<obj-file-path>" --px 4 --py 2 --pz 1
```

### Multiple actions

```
./main -c -s -v -p -i "<obj-file-path>" -o "<stl-file-path>" --px 4 --py 2 --pz 1 --ty 2 --tz 3 --rx 45 --ry 45 --sx 2 --sz 5
```
