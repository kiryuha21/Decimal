#include "../s21_decimal.h"

int s21_is_less(s21_decimal first, s21_decimal second) {
    unsigned int scale;
    if (scale_decimals(&first, &second, &scale) != OK) {
        return FALSE;
    }

    int first_sign = get_sign(&first);
    int second_sign = get_sign(&second);

    if (!is_zero(&first) && !is_zero(&second)) {
        if (first_sign == POSITIVE && second_sign == NEGATIVE) {
            return FALSE;
        } else if (first_sign == NEGATIVE && second_sign == POSITIVE) {
            return TRUE;
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (first.bits[i] < second.bits[i]) {
            return first_sign == POSITIVE ? TRUE : FALSE;
        }
    }

    return FALSE;
}

int s21_is_less_or_equal(s21_decimal first, s21_decimal second) {
  return s21_is_greater(first, second) == TRUE ? FALSE : TRUE;
}

int s21_is_greater(s21_decimal first, s21_decimal second) {
  unsigned int scale;
  if (scale_decimals(&first, &second, &scale) != OK) {
    return FALSE;
  }

  int first_sign = get_sign(&first);
  int second_sign = get_sign(&second);

  if (!is_zero(&first) && !is_zero(&second)) {
    if (first_sign == POSITIVE && second_sign == NEGATIVE) {
      return TRUE;
    } else if (first_sign == NEGATIVE && second_sign == POSITIVE) {
      return FALSE;
    }
  }

  for (int i = 0; i < 3; ++i) {
    if (first.bits[i] > second.bits[i]) {
      return first_sign == POSITIVE ? TRUE : FALSE;
    }
  }

  return FALSE;
}

int s21_is_greater_or_equal(s21_decimal first, s21_decimal second) {
  return s21_is_less(first, second) == TRUE ? FALSE : TRUE;
}

int s21_is_equal(s21_decimal first, s21_decimal second) {
  unsigned int scale;
  if (scale_decimals(&first, &second, &scale) != OK) {
    return FALSE;
  }

  for (int i = 0; i < 3; ++i) {
    if (first.bits[i] != second.bits[i]) {
      return FALSE;
    }
  }

  if (!is_zero(&first) && first.bits[3] != second.bits[3]) {
    return FALSE;
  }

  return TRUE;
}

int s21_is_not_equal(s21_decimal first, s21_decimal second) {
  return s21_is_equal(first, second) == TRUE ? FALSE : TRUE;
}
