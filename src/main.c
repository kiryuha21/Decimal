#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0},
              b = {6, 0, 0, 0x000A0000}, c = DEFAULT_DECIMAL;
  s21_add(a, b, &c);
}
