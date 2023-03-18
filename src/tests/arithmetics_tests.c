#include <stdio.h>

#include "s21_decimal_testing.h"

// -----------add incorrect inp-----------
START_TEST(add_null_inp) {
  s21_decimal a = DEFAULT_DECIMAL, b = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, NULL), ERROR);
}
END_TEST

START_TEST(add_too_lardge_inp) {
  s21_decimal a = MAX_DECIMAL, b = MAX_DECIMAL, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), ERROR);
}
END_TEST

START_TEST(add_too_small_inp) {
  s21_decimal a = MIN_DECIMAL, b = MIN_DECIMAL, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), ERROR);
}
END_TEST

// -----------add correct inp-------------
START_TEST(add_positive_numb) {
  s21_decimal a = {5, 0, 0, 0}, b = {5, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 10);
}
END_TEST

START_TEST(add_positive_greater_negative_numb) {
  s21_decimal a = {7, 0, 0, 0}, b = {5, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 2);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(add_positive_less_negative_numb) {
  s21_decimal a = {5, 0, 0, 0}, b = {7, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 2);
  ck_assert(c.bits[3] & (NEGATIVE_DECIMAL));
}
END_TEST

START_TEST(add_negative_numb) {
  s21_decimal a = {7, 0, 0, NEGATIVE_DECIMAL}, b = {5, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 12);
}
END_TEST

START_TEST(add_opposite_numb) {
  s21_decimal a = {7, 0, 0, NEGATIVE_DECIMAL}, b = {7, 0, 0, 0},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 0);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(add_shift_0_to_1_bits) {
  s21_decimal a = {NEGATIVE_DECIMAL, 0, 0, 0}, b = {NEGATIVE_DECIMAL, 0, 0, 0},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[1], 1);
  ck_assert_uint_eq(c.bits[0], 0);
}
END_TEST

START_TEST(add_shift_1_to_0_bits) {
  s21_decimal a = {0, 1, 0, 0}, b = {NEGATIVE_DECIMAL, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert(c.bits[0] & (NEGATIVE_DECIMAL));
  ck_assert_uint_eq(c.bits[1], 0);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(add_shift_1_to_2_bits) {
  s21_decimal a = {0, NEGATIVE_DECIMAL, 0, 0}, b = {0, NEGATIVE_DECIMAL, 0, 0},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[2], 1);
  ck_assert_uint_eq(c.bits[1], 0);
}
END_TEST

START_TEST(add_shift_2_to_1_bits) {
  s21_decimal a = {0, 0, 1, 0}, b = {0, NEGATIVE_DECIMAL, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert(c.bits[1] & (NEGATIVE_DECIMAL));
  ck_assert_uint_eq(c.bits[2], 0);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(add_positive_fractional_numb) {
  s21_decimal a = {5, 0, 0, 0}, b = {5, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_add(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 10);
}
END_TEST

// -----------sub correct inp-----------

START_TEST(sub_first_greater_second) {
  s21_decimal a = {7, 0, 0, 0}, b = {5, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 2);
  ck_assert_uint_eq(c.bits[3], 0);
}
END_TEST

START_TEST(sub_first_less_second) {
  s21_decimal a = {5, 0, 0, 0}, b = {7, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 2);
  ck_assert(c.bits[3] & (NEGATIVE_DECIMAL));
}
END_TEST

START_TEST(sub_first_negative_second_positive) {
  s21_decimal a = {7, 0, 0, NEGATIVE_DECIMAL}, b = {5, 0, 0, 0},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 12);
  // ck_assert_uint_eq(c.bits[3] && , NEGATIVE_DECIMAL) don't work
  ck_assert(c.bits[3] & (NEGATIVE_DECIMAL));
}
END_TEST

START_TEST(sub_euqal_negative_number) {
  s21_decimal a = {7, 0, 0, NEGATIVE_DECIMAL}, b = {7, 0, 0, NEGATIVE_DECIMAL},
              c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 0);
}
END_TEST

START_TEST(sub_euqal_positive_number) {
  s21_decimal a = {7, 0, 0, 0}, b = {7, 0, 0, 0}, c = DEFAULT_DECIMAL;

  ck_assert_int_eq(s21_sub(a, b, &c), OK);
  ck_assert_uint_eq(c.bits[0], 0);
}
END_TEST

Suite *get_arithmetics_suite() {
  Suite *s;
  TCase *t_case;

  s = suite_create("Arithmetics suite");

  t_case = tcase_create("Add incorrect inp");
  tcase_add_test(t_case, add_null_inp);
  tcase_add_test(t_case, add_too_lardge_inp);
  tcase_add_test(t_case, add_too_small_inp);
  suite_add_tcase(s, t_case);

  t_case = tcase_create("Add correct inp");
  tcase_add_test(t_case, add_positive_numb);
  tcase_add_test(t_case, add_positive_greater_negative_numb);
  tcase_add_test(t_case, add_positive_less_negative_numb);
  tcase_add_test(t_case, add_negative_numb);
  tcase_add_test(t_case, add_opposite_numb);
  tcase_add_test(t_case, add_shift_0_to_1_bits);
  tcase_add_test(t_case, add_shift_1_to_0_bits);
  tcase_add_test(t_case, add_shift_1_to_2_bits);
  tcase_add_test(t_case, add_shift_2_to_1_bits);
  suite_add_tcase(s, t_case);

  t_case = tcase_create("Sub correct inp");
  tcase_add_test(t_case, sub_first_greater_second);
  tcase_add_test(t_case, sub_first_less_second);
  tcase_add_test(t_case, sub_first_negative_second_positive);
  tcase_add_test(t_case, sub_euqal_negative_number);
  tcase_add_test(t_case, sub_euqal_positive_number);
  suite_add_tcase(s, t_case);

  return s;
}

// TODO: remove

START_TEST(decimal_add_1) {
  s21_decimal x = {{4294967295, 4294967295, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 1 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_2) {
  s21_decimal x = {{20, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967295 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_3) {
  s21_decimal x = {{20, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "41 1 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_4) {
  s21_decimal x = {{20, 1, 0, 0}};
  s21_decimal y = {{21, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967295 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_5) {
  s21_decimal x = {{20, 0, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_6) {
  s21_decimal x = {{25, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4 1 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_7) {
  s21_decimal x = {{100, 0, 0, 2147483648}};
  s21_decimal y = {{100, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_8) {
  s21_decimal x = {{99, 0, 0, 0}};
  s21_decimal y = {{100, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_9) {
  s21_decimal x = {{0, 0, 300000000, 1835008}};
  s21_decimal y = {{0, 0, 300000000, 1835008}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 6 1310720";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_10) {
  s21_decimal x = {{0, 0, 3000000000, 0}};
  s21_decimal y = {{0, 0, 3000000000, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = s21_add(x, y, &z);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(decimal_add_11) {
  s21_decimal x = {{1, 0, 0, 1835008}};
  s21_decimal y = {{1, 0, 0, 2149318656}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_add_1) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, 65536}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "2 2 2 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_add_2) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1000000001 1000000001 1000000001 655360";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_add_3) {
  s21_decimal x = {{24, 1, 1, -2147418112}};
  s21_decimal y = {{1, 15, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "2525163519 999999990 999999999 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_add_4) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{1, 1, 1, -2147418112}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "999999999 999999999 999999999 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_add() {
  Suite *suite = suite_create("s21_add");
  TCase *tcase = tcase_create("s21_add");
  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, decimal_add_1);
  tcase_add_test(tcase, decimal_add_2);
  tcase_add_test(tcase, decimal_add_3);
  tcase_add_test(tcase, decimal_add_4);
  tcase_add_test(tcase, decimal_add_5);
  tcase_add_test(tcase, decimal_add_6);
  tcase_add_test(tcase, decimal_add_7);
  tcase_add_test(tcase, decimal_add_8);
  tcase_add_test(tcase, decimal_add_9);
  tcase_add_test(tcase, decimal_add_10);
  tcase_add_test(tcase, decimal_add_11);
  tcase_add_test(tcase, verter_add_1);
  tcase_add_test(tcase, verter_add_2);
  tcase_add_test(tcase, verter_add_3);
  tcase_add_test(tcase, verter_add_4);

  return suite;
}

START_TEST(decimal_sub_1) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_2) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_3) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_4) {
  s21_decimal x = {{2, 0, 0, 2147483648}};
  s21_decimal y = {{2, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_5) {
  s21_decimal x = {{1, 0, 0, 2147483648}};
  s21_decimal y = {{2, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_6) {
  s21_decimal x = {{2, 0, 0, 2147483648}};
  s21_decimal y = {{1, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_7) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "3 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_sub_8) {
  s21_decimal x = {{2, 0, 0, 2147483648}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "3 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_sub_1) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, -2147418112}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "2 2 2 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_sub_2) {
  s21_decimal x = {{1, 1, 1, -2147418112}};
  s21_decimal y = {{1, 1, 1, -2147418112}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_sub_3) {
  s21_decimal x = {{24, 1, 1, -2147418112}};
  s21_decimal y = {{1, 1, 1, 65536}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char ourRes[1000], expect[1000] = "25 2 2 2147549184";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_sub() {
  Suite *suite = suite_create("s21_sub");
  TCase *tcase = tcase_create("s21_sub");
  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, decimal_sub_1);
  tcase_add_test(tcase, decimal_sub_2);
  tcase_add_test(tcase, decimal_sub_3);
  tcase_add_test(tcase, decimal_sub_4);
  tcase_add_test(tcase, decimal_sub_5);
  tcase_add_test(tcase, decimal_sub_6);
  tcase_add_test(tcase, decimal_sub_7);
  tcase_add_test(tcase, decimal_sub_8);
  tcase_add_test(tcase, verter_sub_1);
  tcase_add_test(tcase, verter_sub_2);
  tcase_add_test(tcase, verter_sub_3);

  return suite;
}
