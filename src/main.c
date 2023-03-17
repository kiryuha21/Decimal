#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {0, 0, 1, 0}, b = {0, 1 << 31, 0, 1 << 31},
              c = DEFAULT_DECIMAL;
  s21_add(a, b, &c);
}
