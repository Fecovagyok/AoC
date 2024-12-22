add_executable(day8
src/dunno_yet.cc
src/main.cc
)

target_include_directories(day8 PRIVATE include)
target_link_libraries(day8 PRIVATE aoc_reader)
target_link_libraries(day8 PRIVATE stuffed_matrix)
