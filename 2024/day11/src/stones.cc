#include "stones.h"

#include <pthread.h>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>

#include "calculator.h"

uint32_t how_many_stones(uint64_t stone, uint16_t i) {
  if (i >= 25) return 1;
  if (stone == 0) return how_many_stones(1, i + 1);
  char num_str[22];
  uint16_t len = my_to_string(num_str, stone);

  if (len % 2 == 0) {
    return how_many_stones(my_to_long(num_str, len / 2), i + 1) +
           how_many_stones(my_to_long(num_str + len / 2, len / 2), i + 1);
  }
  return how_many_stones(stone * 2024, i + 1);
}

void* thread_func(void* in) {
  uint64_t* in_param = static_cast<uint64_t*>(in);
  uint64_t num = *in_param;

  *in_param = how_many_stones(num, 0);
  return NULL;
}

void read_stones(std::ifstream& input) {
  uint64_t in;
  uint32_t count = 0;
  uint64_t storage[8];
  uint32_t i = 0;
  while (!input.eof()) {
    input >> in;
    if (input.fail()) break;
    assert(i < 8);
    storage[i++] = in;
  }

  pthread_t pids[8];
  for (i = 0; i < 8; i++) {
    pthread_create(&pids[i], NULL, thread_func, &storage[i]);
  }
  for (i = 0; i < 8; i++) {
    pthread_join(pids[i], NULL);
    count += storage[i];
  }
  std::cout << count << std::endl;
}
