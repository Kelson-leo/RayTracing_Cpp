# Ray Tracing in One Weekend - C++17 Implementation

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.14+-brightgreen.svg)](https://cmake.org/)

A modern C++17 implementation of Peter Shirley's classic *"Ray Tracing in a Weekend"*.
Each chapter was implemented incrementally, with every feature committed as a standalone step
so the git history tells the full story of the build-up.

## Features (Stage 1)

- **PPM image output** - raw pixel format, no external dependencies
- **Ray-sphere intersection** with surface normals
- **Antialiasing** via random multisampling
- **Materials**: Lambertian (diffuse), Metal (reflection + fuzz), Dielectric (refraction + Fresnel)
- **Positionable camera** with adjustable FOV and orientation
- **Defocus blur** (depth of field) with aperture and focus distance
- **Random scene generator** - ~500 spheres with random materials and placement
- **Unit tests** - 16 tests covering vec3, ray, sphere, and hitable_list (Google Test via FetchContent)
- **Modern C++17**: smart pointers, `constexpr` math, `[[maybe_unused]]`, RAII, move semantics

## Build & Run

```bash
# Build
cmake -B build
cmake --build build

# Render (writes PPM to stdout)
./build/raytracer > output/image.ppm

# Run tests
./build/ray_tracer_tests
```

**Note:** The default resolution (200x100, 100 samples) with ~500 objects takes significant time
because the renderer uses a naive O(n) ray-object intersection loop. A BVH acceleration structure
is planned for Stage 2.

## Requirements

- C++17 compiler (g++ or clang++)
- CMake 3.14+
- Google Test is fetched automatically via FetchContent (internet required on first build)

## Project Structure

```
src/
  vec3.h            - 3D vector class with arithmetic operators
  ray.h             - ray (origin + direction)
  hittable.h        - abstract hittable interface + hit_record
  sphere.h          - sphere intersection
  hitable_list.h    - object container (vector<shared_ptr>)
  camera.h          - positionable camera with defocus blur
  material.h        - abstract material interface
  lambertian.h      - diffuse (Lambertian) material
  metal.h           - reflective material with fuzz
  dielectric.h      - refractive material with Fresnel
  utils.h           - random number generation utilities
  scene.h           - random scene generator
  main.cpp          - entry point
tests/
  test_main.cpp     - test runner
  test_vec3.cpp     - vector math tests
  test_ray.cpp      - ray tests
  test_sphere.cpp   - sphere intersection tests
  test_hitable_list.cpp - object list tests
```

## Roadmap

- [ ] BVH acceleration structure
- [ ] Multithreading (`std::execution` or OpenMP)
- [ ] CLI arguments for output file and resolution
- [ ] Progress indicator via `stderr`
- [ ] Thread-safe random number generation
- [ ] Texture mapping and emissive materials

## Credits

Based on [Ray Tracing in a Weekend](https://raytracing.github.io/) by Peter Shirley.
All rights for the original algorithm and book belong to the author.
