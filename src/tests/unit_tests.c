#include "s21_decimal_testing.h"

int main() {
  // TODO: remove + x
  Suite* suites[SUITES_COUNT + 2] = {
      get_arithmetics_suite(), get_comparisons_suite(), get_conversions_suite(),
      get_extras_suite(),
      // TODO: remove
      suite_s21_add(), suite_s21_sub()

  };

  for (int i = 0; i < SUITES_COUNT + 2; ++i) {
    SRunner* srunner = srunner_create(suites[i]);
    srunner_run_all(srunner, CK_NORMAL);
    srunner_free(srunner);
  }

  return 0;
}
