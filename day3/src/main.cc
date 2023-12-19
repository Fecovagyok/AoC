#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#define BUFF_SIZE 500

uint64_t mr_logic(const std::string& str){
  return 0;
}

class Matrix {
  std::vector<std::string> matrix;
  static constexpr size_t padding = 1;
  size_t columns = 140;
  size_t rows = 140;


 public:
  Matrix(){
    matrix.reserve(rows+2*padding);
    matrix.insert(matrix.begin(), std::string(columns+2*padding, ' '));
    matrix.insert(matrix.cend(), std::string(columns+2*padding, ' '));
  }

  void addRow(std::string& r) {
    if (r.size() != columns) {
      std::cerr << "Saaad" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string mine;
    mine.reserve(r.size()+padding*2);
    mine = r;
    mine.insert(mine.cend(), ' ');
    mine.insert(mine.cbegin(), ' ');
    matrix.insert(matrix.end()-1, std::move(mine));
    rows++;
  }
};

int main() {
  std::ifstream input{"input.txt"};
  if (input.fail()) {
    std::cout << "Balfasz" << std::endl;
    return 1;
  }

  std::string buf;
  buf.reserve(BUFF_SIZE);
  std::getline(input, buf);
  Matrix matrix;
  uint64_t osszeg = 0;
  while (true) {
    if (input.eof()) {
      break;
    }
    if (input.fail()) {
      std::cout << "Balfasz" << std::endl;
      return 1;
    }
    matrix.addRow(buf);
    std::getline(input, buf);
  }
  std::cout << osszeg << std::endl;

  return 0;
}
