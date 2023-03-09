#include "s21_decimal_testing.h"

int main() {
    Suite* suites[SUITES_COUNT] = {
            get_arithmetics_suite(),
            get_comparisons_suite(),
            get_conversions_suite(),
            get_extras_suite()
    };

    for (int i = 0; i < SUITES_COUNT; ++i) {
        SRunner* srunner = srunner_create(suites[i]);
        srunner_run_all(srunner, CK_NORMAL);
        srunner_free(srunner);
    }

    return 0;
}


