add_executable(day7
src/main.cc
src/operator_stuff.cc
src/permutation.cc
)
target_link_libraries(day7 PRIVATE aoc_reader)
target_include_directories(day7 PRIVATE include)
