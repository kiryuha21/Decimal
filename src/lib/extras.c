#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return ERROR;
  }
  *result = value;

  s21_truncate(value, result);

  int exp = (int)get_decimal_exponent(&value);
  if (exp > 0 && get_decimal_sign(&value) == NEGATIVE) {
    result->bits[get_elder_bit_index(&value)] += 1;
  }

  return OK;
}

// TODO: using upper boundary rounding if pure 5
//  not sure if it is correct
int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return ERROR;
  }
  big_decimal big_val = convert(value);
  reduce_exponent(&big_val);

  int overflow = 0;
  big_decimal temp = big_val;
  int exp = (int)get_exponent(&big_val);
  for (int i = 0; i < exp - 1; ++i) {
    big_decimal mod;
    scal_div(temp, 10, &temp, &mod);
    overflow = mod.bits[0] + overflow > 5;
  }

  s21_truncate(value, result);
  if (temp.bits[0] % 10 + overflow > 5 || temp.bits[0] % 10 == 5) {
    handle_decimal_inc(result);
  }

  return OK;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return ERROR;
  }

  big_decimal val = convert(value), res = convert(*result);

  int original_sign = get_sign(&val);
  reduce_exponent(&val);
  *result = value;

  int exp = (int)get_exponent(&val);
  for (int i = 0; i < exp; ++i) {
    big_decimal mod;
    scal_div(res, 10, &res, &mod);
  }
  set_exponent(&res, 0);
  set_sign(&res, original_sign);

  return rconvert(res, result);
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return ERROR;
  }

  big_decimal res = convert(value);

  if (!is_zero(&res)) {
    change_sign(&res);
  }

  return rconvert(res, result);
}
