#include <stdio.h>

#include "s21_decimal.h"

int main() {
  float src = 56.986F;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "56986 0 0 196608";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  printf("res1 - %s, res2 - %s\n", res1, res2);
  printf("n1 is %d, should be %d", n1, 0);
}
