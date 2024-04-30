# matrix_views

## Prerequisites
- A compiler that supports C++20 standard
- CMake
- GTest

## Features
- This is a tiny C++20 library implementing views and iterators for matrices that use flat dense row-by-row storage

## Build and test
```bash
mkdir build && cd build && cmake .. && cmake --build . && clear && ctest
```

## Usage
- Examples of how to use the iterators and the base **matrix** class can be found in the [tests](matrix_views/tests) directory
