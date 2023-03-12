#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) { return OK; }

int s21_round(s21_decimal value, s21_decimal *result) { return OK; }

int s21_truncate(s21_decimal value, s21_decimal *result) { return OK; }

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  if (!is_zero(result)) {
    change_sign(result);
  }
  return OK;
}
