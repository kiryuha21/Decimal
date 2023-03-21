#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal decimal1 = {{16, 0, 0, 0}};
  s21_decimal decimal2 = {{3, 0, 0, 0}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);
}
