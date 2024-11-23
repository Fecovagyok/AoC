
add_executable(day5
  src/day5.cc 
  src/custom_tree.cc
  src/interval_func.cc
)
target_include_directories(day5 PRIVATE include)

add_executable(munka_proba src/proba.c)
