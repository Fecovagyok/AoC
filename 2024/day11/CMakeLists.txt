add_executable(day11
src/main.cc
src/stones.cc
)
target_link_libraries(day11 PRIVATE aoc_reader)
target_include_directories(day11 PRIVATE include)
