cmake_minimum_required(VERSION 3.12)
project(RAY_TRACER LANGUAGES CXX C)

set(Ray_Tracer_ROOT "${PROJECT_SOURCE_DIR}")

include(FetchContent)
FetchContent_Declare(
    atlas
    GIT_REPOSITORY https://github.com/marovira/atlas.git)
FetchContent_Populate(atlas)
add_subdirectory(${atlas_SOURCE_DIR} ${atlas_BINARY_DIR})

set(Ray_Tracer_INCLUDE
    "${Ray_Tracer_ROOT}/objects.hpp"
    )
set(Ray_Tracer_SOURCE 
    "${Ray_Tracer_ROOT_ROOT}/main.cpp"
    )

source_group("include" FILES ${Ray_Tracer_INCLUDE})
source_group("source" FILES ${Ray_Tracer_SOURCE})

add_executable(Ray_Tracer ${Ray_Tracer_INCLUDE} ${Ray_Tracer_SOURCE} ${Ray_Tracer_ROOT_SHADER})
target_link_libraries(Ray_Tracer PUBLIC atlas::atlas)
