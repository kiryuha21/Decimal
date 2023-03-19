#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return ERROR;
  }

  unsigned int scale;
  int ret = scale_decimals(&value_1, &value_2, &scale);

  unsigned long long overflow = 0;
  if (ret == TOO_SMALL) {
    overflow = value_2.bits[2];
    value_2.bits[2] = 0;
    scale_decimals(&value_1, &value_2, &scale);
  } else if (ret == TOO_LARGE) {
    overflow = value_1.bits[2];
    value_1.bits[2] = 0;
    scale_decimals(&value_1, &value_2, &scale);
  }

  set_exponent(result, scale);

  if (get_sign(&value_1) == get_sign(&value_2)) {
    int additional_bit = add_same_signs(value_1, value_2, result);
    overflow += additional_bit;
    return try_add_overflow(result, overflow);
  }

  return sub_diff_signs(value_1, value_2, result);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  change_sign(&value_2);

  return s21_add(value_1, value_2, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return ERROR;
  }

  null_decimal(result);

  int ret = mul_without_signs(value_1, value_2, result);
  if (ret != OK) {
    return ret;
  }

  set_exponent(result, get_exponent(&value_1) + get_exponent(&value_2));

  int first_sign = get_sign(&value_1), second_sign = get_sign(&value_2);
  if (first_sign != second_sign) {
    set_sign(result, NEGATIVE);
  } else {
    set_sign(result, POSITIVE);
  }

  reduce_exponent(result);

  return OK;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return OK;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return OK;
}
