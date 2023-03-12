#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  null_decimal(result);
  unsigned int scale;
  int ret = scale_decimals(&value_1, &value_2, &scale);
  set_exponent(result, scale);
  if (get_sign(&value_1) == POSITIVE && get_sign(&value_2) == POSITIVE) {
    ret = add_one_sign_decimals(&value_1, &value_2, result);
    set_sign(result, POSITIVE);
  } else if (get_sign(&value_1) == NEGATIVE && get_sign(&value_2) == NEGATIVE) {
    ret = add_one_sign_decimals(&value_1, &value_2, result);
    set_sign(result, NEGATIVE);
  } else if (get_sign(&value_1) == NEGATIVE && get_sign(&value_2) == POSITIVE) {
    ret = sub_diff_sign_decimals(&value_1, &value_2,
                                 result);  // TODO: handle res sign in sub
  } else if (get_sign(&value_1) == POSITIVE && get_sign(&value_2) == NEGATIVE) {
    ret = sub_diff_sign_decimals(&value_1, &value_2,
                                 result);  // TODO: handle res sign in sub
  }
  return ret;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  null_decimal(result);
  unsigned int scale;
  int ret = scale_decimals(&value_1, &value_2, &scale);
  set_exponent(result, scale);
  if (get_sign(&value_1) == POSITIVE && get_sign(&value_2) == NEGATIVE) {
    ret = add_one_sign_decimals(&value_1, &value_2, result);
    set_sign(result, POSITIVE);
  } else if (get_sign(&value_1) == NEGATIVE && get_sign(&value_2) == POSITIVE) {
    ret = add_one_sign_decimals(&value_1, &value_2, result);
    set_sign(result, NEGATIVE);
  } else if (get_sign(&value_1) == POSITIVE && get_sign(&value_2) == POSITIVE) {
    ret = sub_diff_sign_decimals(&value_1, &value_2,
                                 result);  // TODO: handle res sign in sub
  } else if (get_sign(&value_1) == NEGATIVE && get_sign(&value_2) == NEGATIVE) {
    ret = add_one_sign_decimals(&value_1, &value_2,
                                result);  // TODO: handle res sign in sub
  }
  return ret;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return OK;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return OK;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return OK;
}
