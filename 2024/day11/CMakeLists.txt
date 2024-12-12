add_executable(day11
src/main.cc
src/stones.cc
src/calculator.cc
)
target_link_libraries(day11 PRIVATE pthread)
target_include_directories(day11 PRIVATE include)
