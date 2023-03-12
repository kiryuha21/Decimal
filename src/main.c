#include <stdio.h>

#include "s21_decimal.h"

int main() {
  // Probably better move into tests than delete from main
  s21_decimal a = DEFAULT_DECIMAL;
  set_sign(&a, NEGATIVE);
  printf("%s\n", get_sign(&a) == POSITIVE ? "pos" : "neg");
  set_sign(&a, POSITIVE);
  printf("%s\n", get_sign(&a) == POSITIVE ? "pos" : "neg");
  a.bits[3] = 0x0CFAC000;
  printf("%#X\n", get_exponent(&a));
  set_exponent(&a, 0xAA);
  printf("%#X\n", a.bits[3]);
}
