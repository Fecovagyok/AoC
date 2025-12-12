add_executable(day12 main.cc)
target_link_libraries(day12 aoc_reader me_split me_conversion)

# At least these worked like a charm
# target_compile_options(day12 PRIVATE -fsanitize=address)
# target_link_options(day12 PRIVATE -fsanitize=address)
