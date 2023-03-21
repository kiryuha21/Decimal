#include "s21_decimal_testing.h"

int main() {
  Suite* suites[] = {
      get_arithmetics_suite(), get_comparisons_suite(), get_conversions_suite(),
      get_extras_suite(),
      // TODO: remove
      suite_s21_add(), suite_s21_sub(), suite_s21_negate(),
      suite_s21_is_equal(), suite_s21_is_greater_or_equal(),
      suite_s21_is_greater(), suite_s21_is_less_or_equal(), suite_s21_is_less(),
      suite_s21_is_not_equal(), suite_s21_mul(), suite_s21_floor(),
      suite_s21_from_decimal_to_float(), suite_s21_from_decimal_to_int(),
      suite_s21_from_float_to_decimal(), suite_s21_from_int_to_decimal(),
      suite_s21_round(), suite_s21_truncate(), suite_s21_mod(),
      suite_s21_div()};

  // TODO: remove + x
  for (int i = 0; i < SUITES_COUNT; ++i) {
    SRunner* srunner = srunner_create(suites[i]);
    srunner_run_all(srunner, CK_NORMAL);
    srunner_free(srunner);
  }

  return 0;
}
