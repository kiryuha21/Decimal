#include <stdlib.h>

#include "../s21_decimal.h"

int s21_is_less(s21_decimal first, s21_decimal second) {
  unsigned int scale;
  scale_decimals(&first, &second, &scale, NULL);

  int first_sign = get_sign(&fir);
  int second_sign = get_sign(&sec);

  if (!is_zero(&fir) && !is_zero(&sec)) {
    if (first_sign == POSITIVE && second_sign == NEGATIVE) {
      return FALSE;
    } else if (first_sign == NEGATIVE && second_sign == POSITIVE) {
      return TRUE;
    }
  }

  for (int i = BIG_TOP_BIT; i >= BIG_BOT_BIT; --i) {
    if (fir.bits[i] < sec.bits[i]) {
      return first_sign == POSITIVE ? TRUE : FALSE;
    } else if (fir.bits[i] > sec.bits[i]) {
      return first_sign == POSITIVE ? FALSE : TRUE;
    }
  }

  return FALSE;
}

int s21_is_less_or_equal(s21_decimal first, s21_decimal second) {
  return s21_is_greater(first, second) == TRUE ? FALSE : TRUE;
}

int s21_is_greater(s21_decimal first, s21_decimal second) {
  unsigned int scale;
  scale_decimals(&first, &second, &scale, NULL);

  int first_sign = get_sign(&fir);
  int second_sign = get_sign(&sec);

  if (!is_zero(&fir) && !is_zero(&sec)) {
    if (first_sign == POSITIVE && second_sign == NEGATIVE) {
      return TRUE;
    } else if (first_sign == NEGATIVE && second_sign == POSITIVE) {
      return FALSE;
    }
  }

  for (int i = BIG_TOP_BIT; i >= BIG_BOT_BIT; --i) {
    if (fir.bits[i] > sec.bits[i]) {
      return first_sign == POSITIVE ? TRUE : FALSE;
    } else if (fir.bits[i] < sec.bits[i]) {
      return first_sign == POSITIVE ? FALSE : TRUE;
    }
  }

  return FALSE;
}

int s21_is_greater_or_equal(s21_decimal first, s21_decimal second) {
  return s21_is_less(first, second) == TRUE ? FALSE : TRUE;
}

int s21_is_equal(s21_decimal first, s21_decimal second) {
  unsigned int scale;
  scale_decimals(&first, &second, &scale, NULL);

  for (int i = BOT_BIT; i <= TOP_BIT; ++i) {
    if (first.bits[i] != second.bits[i]) {
      return FALSE;
    }
  }

  if (!is_zero(&fir) && fir.bits[BIG_SPEC_BIT] != sec.bits[BIG_SPEC_BIT]) {
    return FALSE;
  }

  return TRUE;
}

int s21_is_not_equal(s21_decimal first, s21_decimal second) {
  return s21_is_equal(first, second) == TRUE ? FALSE : TRUE;
}
