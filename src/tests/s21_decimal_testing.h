#ifndef C5_S21_DECIMAL_0_S21_DECIMAL_TESTING_H
#define C5_S21_DECIMAL_0_S21_DECIMAL_TESTING_H

#include <check.h>

#include "../s21_decimal.h"

#define MAX_DECIMAL   \
  {                   \
    { -1, -1, -1, 0 } \
  }
#define MIN_DECIMAL                    \
  {                                    \
    { -1, -1, -1, (NEGATIVE_DECIMAL) } \
  }

#define SUITES_COUNT 4

Suite *get_arithmetics_suite();
Suite *get_comparisons_suite();
Suite *get_conversions_suite();
Suite *get_extras_suite();

// TODO: remove
Suite *suite_s21_add();
Suite *suite_s21_sub();
Suite *suite_s21_negate();
Suite *suite_s21_is_equal();
Suite *suite_s21_is_greater_or_equal();
Suite *suite_s21_is_greater();
Suite *suite_s21_is_less_or_equal();
Suite *suite_s21_is_less();
Suite *suite_s21_is_not_equal();

#endif  // C5_S21_DECIMAL_0_S21_DECIMAL_TESTING_H
