#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {10, 0, 0, NEGATIVE_DECIMAL}, b = {7, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;
  s21_sub(a, b, &c);
}
