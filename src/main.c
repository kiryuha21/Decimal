#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {2, 0, 0, NEGATIVE_DECIMAL}, b = {0, 0xFFFFFFFF, 0, 0},
              c = DEFAULT_DECIMAL;
  int ret = s21_mul(a, b, &c);
  print_decimal(&c);
  printf("%i", ret);
}
