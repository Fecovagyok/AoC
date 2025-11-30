#include <iostream>
#include <string>

template <typename... ArgPack>
static std::string rageStringConstructor(ArgPack... Args) {
  std::size_t size = (std::strlen(Args) + ...);
  std::string ret;
  ret.reserve(size);
  (ret.append(Args), ...);
  return ret;
}

int main() {
  std::string dynamic = "asdasdasd";
  std::string kalap =
      rageStringConstructor("kalapos", "kalapos", dynamic.c_str());
  std::cout << kalap << std::endl;
  return 0;
}
