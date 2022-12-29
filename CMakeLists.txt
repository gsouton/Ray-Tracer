cmake_minimum_required(VERSION 3.22)
project(RayTracer)

set(CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add vendors
set(vendors ${CMAKE_CURRENT_SOURCE_DIR}/vendors)
add_subdirectory(${vendors}/glm)

# include_directories(${vendors}/glm/glm)

set(src main.cpp)


add_executable(main ${src})
target_link_libraries(main glm::glm)
# target_include_directories(main glm)


