#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {{1, 1, 1, -2147418112}}, b = {0, 0xFFFFFFFF, 0, 0},
              c = DEFAULT_DECIMAL;
  int ret = s21_sub(a, a, &c);
  print_decimal(&c);
  printf("%i", ret);
}
