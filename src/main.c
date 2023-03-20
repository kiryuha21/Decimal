#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000},
              b = {6, 0, 0, 0x00020000}, c = DEFAULT_DECIMAL;
  int ret = s21_add(a, b, &c);
  printf("ret - %i\n", ret);
  print_decimal(&c);
}
