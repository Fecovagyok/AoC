add_executable(day11 main.cc)

if(WIN32)
  set(LEMON_DIR C:/opt/lemon/cmake)
  set(LEMON_ROOT C:/opt/lemon)
endif()
find_package(LEMON REQUIRED)
target_link_libraries(day11 LEMON::lemon aoc_reader me_split)

