
set(perl_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/day3.pl)

add_custom_target(day3_perl
COMMAND perl ${perl_sources} ${CMAKE_CURRENT_SOURCE_DIR}
SOURCES ${perl_sources})

