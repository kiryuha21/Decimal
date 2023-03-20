#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0},
              b = {4, 0, 0, 0x00010000}, c = DEFAULT_DECIMAL;

  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal y = {{6, 0, 0, 65536}};
  s21_decimal z = {{0, 0, 0, 0}};
  int ret = s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0XFFFFFFFF 0XFFFFFFFF 0XFFFFFFFF 00000000";
  snprintf(ourRes, sizeof(char) * 1000, "%#.8X %#.8X %#.8X %#.8X", z.bits[0],
           z.bits[1], z.bits[2], z.bits[3]);
  printf("%s", ourRes);
}
