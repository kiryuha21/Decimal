#include <stdio.h>

#include "s21_decimal.h"

int main() {
  // Probably better move into tests than delete from main
  s21_decimal a = DEFAULT_DECIMAL, b = {{1, 2, 3, 0x00A10000}},
              c = {{3, 2, 1, 0x00A00000}};
  float f;
  s21_from_decimal_to_float(a, &f);
  set_sign(&a, NEGATIVE);
  printf("%s\n", get_sign(&a) == POSITIVE ? "pos" : "neg");
  set_sign(&a, POSITIVE);
  printf("%s\n", get_sign(&a) == POSITIVE ? "pos" : "neg");
  a.bits[3] = 0x0CFAC000;
  printf("%#X\n", get_exponent(&a));
  set_exponent(&a, 0xAA);
  printf("%#X\n", a.bits[3]);
  s21_add(b, c, &a);
  a = create_decimal(55, 0, 0, 0x00010000);
  s21_add(a, a, &b);
  scal_mul(a, 10, &a);
  a = create_decimal(1 << 31, 0, 0, 0);
  s21_add(a, a, &b);
  a = create_decimal(1 << 31, 0, 0, 0);
  c = create_decimal((1 << 31) - 5, 0, 0, 0);
  s21_sub(a, c, &b);
}
