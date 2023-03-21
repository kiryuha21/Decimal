#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal x = {{150000008, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&x, 3);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[100], expect[100] = "8 0 0 196608";
  snprintf(ourRes, sizeof(char) * 100, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  printf("%s", ourRes);
}
