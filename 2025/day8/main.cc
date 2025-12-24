#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <list>
#include <ostream>
#include <string_view>
#include <unordered_set>
#include <vector>

#include "aoc_reader.h"
#include "me_conversion.h"
#include "me_split.h"

struct Circuit;

struct JunctionBox {
  int32_t coords[3];
  std::list<Circuit>::iterator circuit;
  bool circuit_connected = false;

  double operator-(const JunctionBox& other) const {
    uint64_t sum_squared = 0;
    for (int i = 0; i < 3; i++) {
      int64_t coord_diff =
          static_cast<int64_t>(this->coords[i] - other.coords[i]);
      sum_squared += static_cast<uint64_t>(coord_diff * coord_diff);
    }
    return sqrt(sum_squared);
  }

  const int32_t& operator[](size_t idx) const { return coords[idx]; }

  bool operator==(const JunctionBox other) const noexcept {
    return other.coords[0] == coords[0] && other.coords[1] == coords[1] &&
           other.coords[2] == coords[2];
  }
};

struct JunctionBoxConnection {
  JunctionBox first;
  JunctionBox second;
  bool operator==(const JunctionBoxConnection& other) const noexcept {
    return first == other.first && second == other.second;
  }
};

struct Circuit {
  std::unordered_set<JunctionBox*> boxes;

  void push_back(JunctionBox* box) { boxes.insert(box); }
};

struct DistanceData {
  double distance;
  bool connected;
};

namespace std {
template <>
struct hash<JunctionBoxConnection> {
  uint64_t operator()(const JunctionBoxConnection& c) const noexcept {
    return (static_cast<uint64_t>(c.first.coords[0]) << 53) ^
           (static_cast<uint64_t>(c.first.coords[1]) << 43) ^
           (static_cast<uint64_t>(c.first[2]) << 33) ^
           (static_cast<uint64_t>(c.second[0]) << 23) ^
           (static_cast<uint64_t>(c.second[1]) << 13) ^
           (static_cast<uint64_t>(c.second[2])) ^ (c.first[0] >> 21);
  }
};
}  // namespace std

std::ostream& operator<<(std::ostream& os, const JunctionBox& box) {
  return os << box.coords[0] << "," << box.coords[1] << "," << box.coords[2]
            << "\n";
}

std::vector<JunctionBox> boxes;
std::unordered_set<JunctionBoxConnection> connection_set;
DistanceData connection_data[1000][1000];
// std::unordered_map<JunctionBox, Circuit*> circuit_map;
std::list<Circuit> circuit_list;

void ciruit_mergin_stuff(JunctionBox& one, JunctionBox& other) {
  if (!one.circuit_connected && !other.circuit_connected) {
    Circuit circuit{{&one, &other}};
    auto circuit_iter =
        circuit_list.insert(circuit_list.cend(), std::move(circuit));

    one.circuit = circuit_iter;
    other.circuit = circuit_iter;
    one.circuit_connected = true;
    other.circuit_connected = true;
    return;
  }

  if (!one.circuit_connected) {
    other.circuit->push_back(&one);
    one.circuit = other.circuit;
    one.circuit_connected = true;
    return;
  }

  if (!other.circuit_connected) {
    one.circuit->push_back(&other);
    other.circuit = one.circuit;
    other.circuit_connected = true;
    return;
  }

  if (one.circuit == other.circuit) {
    return;
  }

  std::list<Circuit>::iterator disposed_circuit = other.circuit;
  std::unordered_set<JunctionBox*>& winner_circuit = one.circuit->boxes;
  std::unordered_set<JunctionBox*>& disposed_circuit_vector =
      disposed_circuit->boxes;
  for (JunctionBox* box : disposed_circuit_vector) {
    box->circuit = one.circuit;
  }
  winner_circuit.merge(disposed_circuit_vector);
  circuit_list.erase(disposed_circuit);
}

void connect_first_pair() {
  double min = boxes[0] - boxes[1];
  size_t idx1 = 0, idx2 = 1;
  for (size_t i = 0; i < boxes.size(); i++) {
    for (size_t j = i + 1; j < boxes.size(); j++) {
      double distance = boxes[i] - boxes[j];
      connection_data[i][j].distance = distance;
      if (distance < min) {
        min = distance;
        idx1 = i;
        idx2 = j;
      }
    }
  }
  JunctionBox& one = boxes[idx1];
  JunctionBox& other = boxes[idx2];
  connection_data[idx1][idx2].connected = true;
  ciruit_mergin_stuff(one, other);
}

void connect_all_other_pairs() {
  double min = std::numeric_limits<double>::max();
  size_t idx1, idx2;
  for (size_t i = 0; i < boxes.size(); i++) {
    for (size_t j = i + 1; j < boxes.size(); j++) {
      if (connection_data[i][j].connected) {
        continue;
      }
      double distance = connection_data[i][j].distance;
      if (distance < min) {
        min = distance;
        idx1 = i;
        idx2 = j;
      }
    }
  }
  JunctionBox& one = boxes[idx1];
  JunctionBox& other = boxes[idx2];
  connection_data[idx1][idx2].connected = true;
  ciruit_mergin_stuff(one, other);
}

bool comparator(const Circuit& lhs, const Circuit& rhs) {
  return lhs.boxes.size() > rhs.boxes.size();
}

void parse(std::string& line) {
  boxes.reserve(1000);
  auto pieces = split(line, ',');
  assert(pieces.size());
  JunctionBox& box = boxes.emplace_back();
  for (int i = 0; i < 3; i++) {
    box.coords[i] = str_to_int32(pieces[i]);
  }
}

int main() {
  auto cb = [](std::string& line) { parse(line); };
  AoCReader reader{cb, 256, "2025/day8/input.txt"};
  reader.read();
  connect_first_pair();
  for (int i = 0; i < 999; i++) {
    connect_all_other_pairs();
  }
  std::vector<Circuit> vector_list(circuit_list.cbegin(), circuit_list.cend());
  std::sort(vector_list.begin(), vector_list.end(), comparator);
  uint64_t product = 1;
  for (size_t i = 0; i < 3; i++) {
    product = product * vector_list.at(i).boxes.size();
  }
  std::cout << product << std::endl;
  return 0;
}
