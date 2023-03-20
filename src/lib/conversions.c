#include <limits.h>
#include <math.h>
#include <stdio.h>

#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) {
    return ERROR;
  }

  null_decimal(dst);
  if (src < 0) {
    set_sign(dst, NEGATIVE);
    src = -src;
  }
  dst->bits[0] = src;

  return OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL) {
    return ERROR;
  }

  if (src != 0 && fabsf(src) < 1e-28) {
    null_decimal(dst);
    return ERROR;
  }

  if (src == INFINITY || src == NAN) {
    return ERROR;
  }

  null_decimal(dst);
  if (src < 0) {
    set_sign(dst, NEGATIVE);
    src = -src;
  }

  int integer_digits = 0;
  for (float src_cp = src; src_cp > 1; src_cp /= 10, ++integer_digits) {
  }

  int leading_zeros = 0;
  for (; src != 0 && src < 1; src *= 10, ++leading_zeros) {
  }

  int significant_digits = snprintf(NULL, 0, "%g", src) - 1;
  significant_digits = significant_digits > 7 ? 7 : significant_digits;

  if (leading_zeros > 0) {
    src /= 10;
    --leading_zeros;
  }
  int exp = significant_digits - integer_digits;
  set_exponent(dst, exp + leading_zeros);

  dst->bits[0] = (unsigned int)(src * powf(10, (float)exp));

  return OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) {
    return ERROR;
  }

  s21_decimal integer_src;
  s21_truncate(src, &integer_src);
  reduce_exponent(&src);

  if (get_elder_bit_index(&integer_src) != 0) {
    return ERROR;
  }

  if (integer_src.bits[0] > INT_MAX) {
    return ERROR;
  }

  *dst = (int)integer_src.bits[0];
  if (get_sign(&integer_src) == NEGATIVE) {
    *dst = -(*dst);
  }

  return OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return ERROR;
  }

  reduce_exponent(&src);

  int int_part;
  float float_part;

  if (s21_from_decimal_to_int(src, &int_part) != OK) {
    return ERROR;
  }

  unsigned int exp = get_exponent(&src);
  float power = powf(10, (float)exp);
  float_part = (float)(src.bits[0] % (int)power) * powf(0.1F, (float)exp);
  if (get_sign(&src) == NEGATIVE) {
    float_part = -float_part;
  }

  *dst = (float)int_part + float_part;
  return OK;
}
