add_executable(day8 main.cc)
target_link_libraries(day8 aoc_reader me_split me_conversion)

# target_compile_options(day8 PRIVATE -fsanitize=address)
# target_link_options(day8 PRIVATE -fsanitize=address)
