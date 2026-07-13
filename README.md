# Ray Tracing in One Weekend - C++17 Implementation

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.14+-brightgreen.svg)](https://cmake.org/)
[![OpenMP](https://img.shields.io/badge/OpenMP-4.5-blue.svg)](https://www.openmp.org/)
[![Tests](https://img.shields.io/badge/tests-16%2F16-green.svg)]()

A modern C++17 implementation of Peter Shirley's classic *"Ray Tracing in a Weekend"*.
Each chapter was implemented incrementally, with every feature committed as a standalone step
so the git history tells the full story of the build-up.

## Features (Stage 1)

- **PPM image output** - raw pixel format, no external dependencies
- **BVH acceleration** - Bounding Volume Hierarchy for O(log n) ray intersections
- **Multithreading** - OpenMP parallel rendering with per-thread RNG
- **Ray-sphere intersection** with surface normals
- **Antialiasing** via random multisampling (up to 100 samples/pixel)
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

# View (PPM viewers)
feh output/image.ppm           # Linux (feh)
display output/image.ppm       # Linux (ImageMagick)

# Run tests
./build/ray_tracer_tests
```

The output is raw PPM (ASCII). Most image viewers support it (`feh`, `display`, GIMP, Photoshop).
Browsers do not — convert to PNG if needed: `convert output/image.ppm output/image.png`

The default scene contains ~500 objects. BVH + OpenMP keeps render times manageable
(~4.3s for 200x100 at 100 samples on 12 cores).

## Requirements

- C++17 compiler (g++ or clang++)
- CMake 3.14+
- Google Test is fetched automatically via FetchContent (internet required on first build)

## Project Structure

```
src/
  vec3.h            - 3D vector class with arithmetic operators
  ray.h             - ray (origin + direction)
  aabb.h            - axis-aligned bounding box with slab intersection
  hittable.h        - abstract hittable interface + hit_record
  sphere.h          - sphere intersection
  hitable_list.h    - object container (vector<shared_ptr>)
  bvh.h             - BVH acceleration tree
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
## Credits

Based on [Ray Tracing in a Weekend](https://raytracing.github.io/) by Peter Shirley.
All rights for the original algorithm and book belong to the author.
