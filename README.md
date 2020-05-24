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
- **ENABLE_CLANG_TIDY** - Enable clang-tidy; *default*: OFF;

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

## Roadmap

- [x] Design and implement a software architecture for a general 3D file converter, that allows you to read, convert, and write 3D mesh file formats. The architecture should make it possible to easily extend the implementation with new file formats.

- [x] Create a concrete implementation for OBJ->STL conversion (only one direction! From OBJ to binary STL). The OBJ file support should be limited to v, vt, vn and f elements. STL export should be binary STL, not the text version. Note that OBJ supports non triangular faces. You can assume that these are always convex planar faces.

- [x] Allow the user to set a transformation (any combination of rotation, scale, translation) in the converter.
- [x] Calculate the surface area of the model
- [x] (Experimental) Calculate the volume of the model.
- [x] (Experimental) Implement an algorithm that will decide from a 3d point if it is inside or outside the model.
- [ ] Calculate the volume of the model using voxels.
- [ ] Implement an algorithm that will decide from a 3d point if it is inside or outside the model using voxels.
