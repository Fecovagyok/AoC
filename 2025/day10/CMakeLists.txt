
find_package(ortools CONFIG REQUIRED)

add_executable(day10 main.cc machine_stuff.cc)
target_link_libraries(day10 aoc_reader me_split me_conversion ortools::ortools)


#add_executable(day10_test test1.cc machine_stuff.cc)
#target_link_libraries(day10_test aoc_reader me_split me_conversion)
