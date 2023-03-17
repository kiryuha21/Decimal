#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {7, 0, 0, 1 << 31}, b = {7, 0, 0, 0}, c = DEFAULT_DECIMAL;
  s21_add(a, b, &c);
}
