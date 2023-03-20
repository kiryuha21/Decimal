#include <stdio.h>

#include "s21_decimal.h"

int main() {
    s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_add(decimal1, decimal2, &result);
}
