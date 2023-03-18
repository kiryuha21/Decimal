#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {7, 0, 0, NEGATIVE_DECIMAL}, b = {7, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;
  s21_add(a, b, &c);
  print_decimal(&c);
}
