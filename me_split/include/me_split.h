#pragma once

#include <cctype>
#include <cstddef>
#include <string_view>
#include <vector>

inline std::vector<std::string_view> split(const std::string_view line,
                                           char delim = '\0',
                                           size_t initial_size = 10) {
  std::vector<std::string_view> res;
  size_t start = 0;
  res.reserve(initial_size);
  for (size_t i = 0; i < line.size(); i++) {
    if ((delim == '\0' && isspace(line[i])) || line[i] == delim) {
      if (start != i) {
        res.emplace_back(line.substr(start, i - start));
        start = i + 1;
      }
    }
  }
  res.emplace_back(line.substr(start));
  return res;
}
