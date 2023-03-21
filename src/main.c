#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal x = {{14425, 1, 1, 0}};
  s21_decimal y = {{14425, 1, 1, 0}};
  s21_decimal *z = NULL;
  set_exponent(&x, 22);
  set_exponent(&y, 22);
  int err = 0;
  err = s21_mod(x, y, z);
}
