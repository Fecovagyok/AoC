#ifndef READIN_H
#define READIN_H

#include <cstddef>
#ifdef __cplusplus

#include <functional>
#include <iostream>
#include <string>

class AoCReader {
  std::string buf;
  static constexpr size_t default_size = 150;
  std::function<void(std::string&)> callback;
  std::function<void(void)> end_callback;
  const char* const file_name;

 public:
  AoCReader(AoCReader&) = delete;
  AoCReader(AoCReader&&) = delete;
  AoCReader& operator=(AoCReader&) = delete;
  AoCReader& operator=(AoCReader&&) = delete;

  AoCReader(std::function<void(std::string&)> cb, size_t n = default_size,
            const char* f = "input.txt",
            std::function<void(void)> end_cb = nullptr)
      : callback{cb}, end_callback{end_cb}, file_name{f} {
    std::ios_base::sync_with_stdio(false);
    buf.reserve(n);
  }

  int read();
  ~AoCReader() = default;
};

#endif  //! __cplusplus
#endif  //! READIN_H
