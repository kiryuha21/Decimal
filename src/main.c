#include <stdio.h>

#include "s21_decimal.h"

int main() {
    s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal y = {{6, 0, 0, 0x000A0000}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = s21_add(x, y, &z);
}
