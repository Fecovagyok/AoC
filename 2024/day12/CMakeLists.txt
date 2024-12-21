add_executable(day12
src/main.cc
src/garden.cc
)
target_link_libraries(day12 PRIVATE aoc_reader)
target_include_directories(day12 PRIVATE include)

