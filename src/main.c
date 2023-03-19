#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {0xFFFFFFFF, 0, 0, 0}, b = {10, 0, 0, 0x00010000}, c;
  s21_add(a, b, &c);
  print_decimal(&c);
}
