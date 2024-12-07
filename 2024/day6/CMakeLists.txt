add_executable(day6
src/track.cc
src/main.cc)
target_link_libraries(day6 PRIVATE aoc_reader)
target_include_directories(day6 PRIVATE include)
