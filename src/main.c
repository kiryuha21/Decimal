#include <stdio.h>

#include "s21_decimal.h"

int main() {
  big_decimal a = {0xFFFFFFFF, 0, 0, 0, 0, 0}, b = {10, 0, 0, 0, 0, 0x00010000},
              c;
  unsigned int scale;
  scale_decimals(&a, &b, &scale);
  add_same_signs(a, b, &c);
  print_big_decimal(&c);
}
