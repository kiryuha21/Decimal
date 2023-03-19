#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return ERROR;
  }

  big_decimal val1 = convert(value_1), val2 = convert(value_2);
  big_decimal res = {0};

  unsigned int scale;
  if (scale_decimals(&val1, &val2, &scale) != OK) {
    return TOO_LARGE;
  }

  set_exponent(&res, scale);

  int ret = OK;
  if (get_sign(&val1) == get_sign(&val2)) {
    ret = add_same_signs(val1, val2, &res);
  } else {
    ret = sub_diff_signs(val1, val2, &res);
  }
  if (ret != OK) {
    return ret;
  }

  return rconvert(res, result);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  change_decimal_sign(&value_2);

  return s21_add(value_1, value_2, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return ERROR;
  }

  big_decimal val1 = convert(value_1), val2 = convert(value_2);
  big_decimal res = {0};

  unsigned int scale;
  null_decimal(result);
  unsigned int before_exp = get_exponent(&val1);
  if (scale_decimals(&val1, &val2, &scale) != OK) {
    return TOO_LARGE;
  }

  int ret = mul_without_signs(val1, val2, &res);
  set_exponent(&res, scale + before_exp - get_exponent(&res));
  if (ret != OK) {
    return ret;
  }
  int first_sign = get_sign(&val1), second_sign = get_sign(&val2);
  if (first_sign != second_sign) {
    set_sign(&res, NEGATIVE);
  } else {
    set_sign(&res, POSITIVE);
  }

  reduce_exponent(&res);

  return rconvert(res, result);
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return OK;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return OK;
}
