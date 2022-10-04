cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine)

add_subdirectory(include)

set(SOURCE_FILES
  "src/particle.cpp"
)

add_library(moto ${SOURCE_FILES})

target_link_libraries(moto
PUBLIC
  moto_header
)
