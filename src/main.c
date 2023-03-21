#include <stdio.h>

#include "s21_decimal.h"

int main() {
  /*s21_decimal x = {{1, 1, 1, 10 << 16}};
  s21_decimal y = {{1, 10, 1, NEGATIVE_DECIMAL + (15 << 16)}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1019311944 458670364 542101085 2148990976";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  printf("%s", ourRes);*/
  /*s21_decimal start = {{3838104000, 2681241660, 54210108, 1769472}};
  for (int i = 0; i < 10; ++i) {
    s21_decimal test = DEFAULT_DECIMAL;
    add_int_to_dec(start, i, &test);
    reduce_exponent(&test);
    char ourRes[1000];
    snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", test.bits[0],
             test.bits[1], test.bits[2], test.bits[3]);
    printf("%s\n", ourRes);
  }*/
  s21_decimal x = {{1, 0, 0, 0x00030000}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = DEFAULT_DECIMAL;
  int err = 0;
  err = s21_div(x, y, &z);
}
