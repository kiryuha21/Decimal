#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal x = {{125, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exponent(&x, 1);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "5 0 0 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  printf("%s", ourRes);
}
