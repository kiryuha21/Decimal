#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
}
