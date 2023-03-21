#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return ERROR;
  }
  *result = value;

  s21_truncate(value, result);

  int exp = (int)get_exponent(&value);
  if (exp > 0 && get_sign(&value) == NEGATIVE) {
    result->bits[get_elder_bit_index(result)] += 1;
  }

  return OK;
}

// TODO: using upper boundary rounding if pure 5
//  not sure if it is correct
int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return ERROR;
  }
  reduce_exponent(&value);

  s21_decimal temp = value;
  int exp = (int)get_exponent(&value);
  for (int i = 0; i < exp - 1; ++i) {
    div_dec_on_int(temp, 10, &temp);
  }

  s21_truncate(value, result);
  if (temp.bits[0] % 10 >= 5) {
    handle_decimal_inc(result);
  }

  return OK;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return ERROR;
  }

  int original_sign = get_sign(&value);
  reduce_exponent(&value);
  *result = value;

  int exp = (int)get_exponent(&value);
  for (int i = 0; i < exp; ++i) {
    div_dec_on_int(*result, 10, result);
  }
  set_exponent(result, 0);
  set_sign(result, original_sign);

  return OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return ERROR;
  }

  *result = value;

  if (!is_zero(result)) {
    change_sign(result);
  }

  return OK;
}
