#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal x = {{0, 0, 300000000, 1835008}};
  s21_decimal y = {{0, 0, 300000000, 1835008}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 6 1310720";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  printf("%s", ourRes);

  /*s21_decimal a = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0},
              b = {6, 0, 0, 0x00010000}, c = DEFAULT_DECIMAL;
  int ret = s21_add(a, b, &c);
  printf("ret - %i\n", ret);
  print_decimal(&c);*/
}
