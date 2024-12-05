add_executable(day5
src/main.cc
src/pagin.cc
src/rulin.cc
)
target_link_libraries(day5 PRIVATE aoc_reader)
target_include_directories(day5 PRIVATE include)
