#ifndef READIN_H
#define READIN_H

#ifdef __cplusplus

#include <functional>
#include <string>

class AoCReader{
  std::string buf;
  static constexpr size_t default_size = 150;
  std::function<void(const std::string&)> callback;
  const char* const file_name;

 public:
  AoCReader(std::function<void(const std::string&)> cb, const char* f="input.txt",
                 size_t n = default_size)
      : buf{}, callback{cb}, file_name{f} {
    std::ios_base::sync_with_stdio(false);
    buf.reserve(n);
  }

  int read();
};

#endif  //! __cplusplus
#endif  //! READIN_H
