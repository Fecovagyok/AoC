#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 1
#define DEFAULT_SIZE 16
#define OP_SIZE DEFAULT_SIZE - 1
#define NUM_OF_MISSING 4
#define SHRANK_SIZE OP_SIZE - NUM_OF_MISSING
#define NUM_OF_PAIRS DEFAULT_SIZE - NUM_OF_MISSING

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct {
  int array[OP_SIZE];
  uint16_t size;
} Nums;

typedef struct {
  int num;
  int next;
} Pair;

void init_nums(Nums* nums) {
  for (uint16_t i = 0; i < OP_SIZE; i++) {
    nums->array[i] = i + 1;
  }
  nums->size = OP_SIZE;
}

bool is_among_missing(int missing[static NUM_OF_MISSING], int num) {
  for (uint16_t i = 0; i < NUM_OF_MISSING; i++) {
    if (num == missing[i]) return true;
  }
  return false;
}

void init_with_missing(Nums* nums, int missing[static NUM_OF_MISSING]) {
  nums->size = SHRANK_SIZE;
  uint16_t i = 0;
  for (int num = 1; num < OP_SIZE; num++) {
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

void make_pairs(Pair pairs[static NUM_OF_PAIRS], Nums* available_nums) {
  pairs[0].num = 0;
  uint16_t i;
  for (i = 0; i < SHRANK_SIZE; i++) {
    int next_num = get_rand_next(available_nums);
    pairs[i].next = next_num;
    pairs[i + 1].num = next_num;
  }
  pairs[i].next = 0;
}

int main(void) {
  srand(SEED);
  Nums nums;
  init_nums(&nums);
  int missing[NUM_OF_MISSING];

  printf("Missing nums: ");
  for (uint16_t i = 0; i < ARRAY_SIZE(missing); i++) {
    missing[i] = get_rand_next(&nums);
    printf("%d ", missing[i]);
  }
  printf("\n\n");

  init_with_missing(&nums, missing);

  Pair pairs[NUM_OF_PAIRS];
  make_pairs(pairs, &nums);

  for (uint16_t i = 0; i < ARRAY_SIZE(pairs); i++) {
    printf("%d:%d\n", pairs[i].num, pairs[i].next);
  }

  return 0;
}
