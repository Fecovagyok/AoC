#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 1

typedef struct {
  int* ptr;
  uint16_t size;
} Nums;

void init_nums(Nums* nums) {
  nums->ptr = malloc(sizeof(int) * 16);
  for (uint16_t i = 0; i < 16; i++) {
    nums->ptr[i] = i;
  }
  nums->size = 16;
}

void free_nums(Nums nums) { free(nums.ptr); }

void delete_num(Nums* nums, uint16_t idx) {
  if (idx >= nums->size) {
    printf("Bad\n");
    exit(1);
  }
  uint16_t new_size = nums->size - 1;
  int* new = malloc(sizeof(int) * new_size);
  uint16_t new_i = 0;
  for (uint16_t i = 0; i < nums->size; i++) {
    if (i == idx) continue;
    new[new_i] = nums->ptr[i];
    new_i++;
  }
  nums->size = new_size;
  free(nums->ptr);
  nums->ptr = new;
}

int get_rand_next(Nums* nums) {
  int random = rand() % nums->size;
  if (random < 0) {
    printf("Bad random\n");
    exit(1);
  }

  int num = nums->ptr[random];
  delete_num(nums, random);
  return num;
}

int main(void) {
  srand(SEED);
  Nums nums;
  init_nums(&nums);
  int excercise[16];

  for (uint16_t i = 0; i < 16; i++) {
    excercise[i] = get_rand_next(&nums);
    printf("%d: %d\n", i, excercise[i]);
  }

  free_nums(nums);

  return 0;
}
