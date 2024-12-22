#include "aoc_reader.h"

#include <cstddef>
#include <fstream>
#include <iostream>

int AoCReader::read() {
  std::ifstream input{file_name};
  if (input.fail()) {
    std::cerr << "No input file bro" << std::endl;
    return -1;
  }

  while (true) {
    std::getline(input, buf);
    if (input.eof()) {
      break;
    }
    if (input.fail()) {
      std::cerr << "Fail before eof? How did we get here?" << std::endl;
      return -2;
    }
    callback(buf);
  }
  if (end_callback != nullptr) end_callback();
  return 0;
}
