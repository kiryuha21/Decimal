#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  *result = value;

  s21_truncate(value, result);

  int exp = (int)get_exponent(&value);
  if (exp > 0 && get_sign(&value) == NEGATIVE) {
    result->bits[get_elder_bit_index(&value)] += 1;
  }

  return OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  reduce_exponent(&value);

  int exp = (int)get_exponent(&value);
  int first_integer_bit_ind = get_first_integer_bit_index(&value);
  for (int i = first_integer_bit_ind; i >= 0; --i) {
    unsigned int mod = (unsigned int)pow(10.0, (double)(exp % 10));
    for (; mod > 0; mod /= 10, --exp) {
      unsigned int digit = (value.bits[i] % mod) / (mod - 1);
      if (digit != 5) {
        s21_truncate(value, result);
        if (digit > 5) {
          handle_decimal_inc(result);
        }
        return OK;
      }
    }
  }

  // TODO: using upper boundary rounding
  //  not sure if it is correct
  s21_truncate(value, result);
  if (value.bits[0] > 5) {
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
    s21_decimal mod;
    scal_div(*result, 10, result, &mod);
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
