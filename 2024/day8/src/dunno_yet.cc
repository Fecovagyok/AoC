#include "dunno_yet.h"

#include <stuffed_matrix.h>

StuffedMatrix matrix;

void read_row(std::string& buf) { matrix.add_row(buf); }
void read_end() { matrix.row_end(); }
