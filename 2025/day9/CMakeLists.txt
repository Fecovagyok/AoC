add_executable(day9 main.cc)
target_link_libraries(day9 aoc_reader me_split me_conversion)

# At least these worked like a charm
# target_compile_options(day9 PRIVATE -fsanitize=address)
# target_link_options(day9 PRIVATE -fsanitize=address)
