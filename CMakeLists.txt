cmake_minimum_required(VERSION 3.14)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raytracer src/main.cpp)

target_compile_options(raytracer PRIVATE -Wall -Wextra -Wpedantic)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(ray_tracer_tests
    tests/test_main.cpp
    tests/test_vec3.cpp
    tests/test_ray.cpp
    tests/test_sphere.cpp
    tests/test_hitable_list.cpp
)

target_link_libraries(ray_tracer_tests gtest_main pthread)
target_compile_options(ray_tracer_tests PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
add_test(NAME UnitTests COMMAND ray_tracer_tests)