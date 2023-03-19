#include <stdio.h>

#include "s21_decimal.h"

int main() {
    s21_decimal x = {{0, 0, 3000000000, 0}};
    s21_decimal y = {{0, 0, 3000000000, 0}};
    s21_decimal z = {{0, 0, 0, 0}};
    int err = s21_add(x, y, &z);
}
