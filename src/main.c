#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{2, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "100000 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
}
