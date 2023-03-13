#include "../s21_decimal.h"

int s21_is_less(s21_decimal first, s21_decimal second) { return TRUE; }

int s21_is_less_or_equal(s21_decimal first, s21_decimal second) { return TRUE; }

int s21_is_greater(s21_decimal first, s21_decimal second) { return TRUE; }

int s21_is_greater_or_equal(s21_decimal first, s21_decimal second) {
  return TRUE;
}

int s21_is_equal(s21_decimal first, s21_decimal second) {
  int ret = TRUE;
  unsigned int scale;
  if (scale_decimals(&first, &second, &scale) != OK) {
    ret = FALSE;
  }
  for (int i = 0; i < 2; ++i) {
    if (first.bits[i] != second.bits[i]) {
      ret = FALSE;
    }
  }
  if (!is_zero(&first) && first.bits[3] != second.bits[3]) {
    ret = FALSE;
  }
  return ret;
}

int s21_is_not_equal(s21_decimal first, s21_decimal second) { return TRUE; }
