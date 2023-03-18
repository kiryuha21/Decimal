#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {0x10, 0, 0, NEGATIVE_DECIMAL}, b = {0, 1, 0, 0},
              c = DEFAULT_DECIMAL;
  s21_mul(a, b, &c);
  print_decimal(&c);
}
