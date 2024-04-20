#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 1

typedef struct {
  int array[16];
  uint16_t size;
} Nums;

void init_nums(Nums* nums) {
  for (uint16_t i = 0; i < 16; i++) {
    nums->array[i] = i;
  }
  nums->size = 16;
}

bool is_among_missing(int missing[static 4], int num) {
  for (uint16_t i = 0; i < 4; i++) {
    if (num == missing[i]) return true;
  }
  return false;
}

void init_with_missing(Nums* nums, int missing[static 4]) {
  nums->size = 12;
  uint16_t i = 0;
  for (int num = 0; num < 16; num++) {
    if (is_among_missing(missing, num)) continue;
    nums->array[i] = num;
    i++;
  }
}

void delete_num(Nums* nums, uint16_t idx) {
  if (idx >= nums->size) {
    printf("Bad\n");
    exit(1);
  }
  for (uint16_t i = idx; i < nums->size - 1; i++) {
    nums->array[i] = nums->array[i + 1];
  }
  nums->size--;
}

int get_rand_next(Nums* nums) {
  int random = rand() % nums->size;
  if (random < 0) {
    printf("Bad random\n");
    exit(1);
  }

  int num = nums->array[random];
  delete_num(nums, random);
  return num;
}

int main(void) {
  srand(SEED);
  Nums nums;
  init_nums(&nums);
  int missing[4];

  printf("Missing nums: ");
  for (uint16_t i = 0; i < 4; i++) {
    missing[i] = get_rand_next(&nums);
    printf("%d ", missing[i]);
  }
  printf("\n\n");

  init_with_missing(&nums, missing);
  int excercise[12];
  for (uint16_t i = 0; i < 12; i++) {
    excercise[i] = get_rand_next(&nums);
    printf("%d: %d\n", i, excercise[i]);
  }

  return 0;
}
