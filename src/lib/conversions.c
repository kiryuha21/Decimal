#include <limits.h>
#include <float.h>
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

  if (fabsf(src) < 1e-28) {
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

  // FIXME: wrong calculation of significant digits
  float src_cp = src;
  int significant_digits = 0;
  for (; src_cp > FLT_EPSILON && significant_digits <= 7; ++significant_digits) {
    while (src_cp < 1) {
      src_cp *= 10;
    }
    src_cp = remove_elder_digit(src_cp);
  }

  int exp = 7 - significant_digits;
  set_exponent(dst, exp);

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
