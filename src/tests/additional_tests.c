#include <stdio.h>

#include "s21_decimal_testing.h"

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

START_TEST(decimal_is_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_2) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{1747, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_8) {
  s21_decimal x = {{0, 0, 0, NEGATIVE_DECIMAL}};
  s21_decimal y = {{1, 0, 0, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_9) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_10) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_equal() {
  Suite *suite = suite_create("s21_is_equal");
  TCase *tcase = tcase_create("case_s21_is_equal");

  tcase_add_test(tcase, decimal_is_equal_1);
  tcase_add_test(tcase, decimal_is_equal_2);
  tcase_add_test(tcase, decimal_is_equal_3);
  tcase_add_test(tcase, decimal_is_equal_4);
  tcase_add_test(tcase, decimal_is_equal_5);
  tcase_add_test(tcase, decimal_is_equal_6);
  tcase_add_test(tcase, decimal_is_equal_7);
  tcase_add_test(tcase, decimal_is_equal_8);
  tcase_add_test(tcase, decimal_is_equal_9);
  tcase_add_test(tcase, decimal_is_equal_10);

  tcase_add_test(tcase, verter_is_equal_1);
  tcase_add_test(tcase, verter_is_equal_2);
  tcase_add_test(tcase, verter_is_equal_3);
  tcase_add_test(tcase, verter_is_equal_4);
  tcase_add_test(tcase, verter_is_equal_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_greater_or_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_or_equal_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_or_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_or_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_or_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_or_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_or_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};

  int ourRes = s21_is_greater_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_greater_or_equal() {
  Suite *suite = suite_create("s21_greater_or_equal");
  TCase *tcase = tcase_create("case_s21_greater_or_equal");

  tcase_add_test(tcase, decimal_is_greater_or_equal_1);
  tcase_add_test(tcase, decimal_is_greater_or_equal_2);
  tcase_add_test(tcase, decimal_is_greater_or_equal_3);
  tcase_add_test(tcase, decimal_is_greater_or_equal_4);
  tcase_add_test(tcase, decimal_is_greater_or_equal_5);
  tcase_add_test(tcase, decimal_is_greater_or_equal_6);
  tcase_add_test(tcase, decimal_is_greater_or_equal_7);
  tcase_add_test(tcase, decimal_is_greater_or_equal_8);
  tcase_add_test(tcase, verter_is_greater_or_equal_1);
  tcase_add_test(tcase, verter_is_greater_or_equal_2);
  tcase_add_test(tcase, verter_is_greater_or_equal_3);
  tcase_add_test(tcase, verter_is_greater_or_equal_4);
  tcase_add_test(tcase, verter_is_greater_or_equal_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_greater_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_greater(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_greater(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};
  int ourRes = s21_is_greater(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_greater_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_greater(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_greater_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_greater(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_greater() {
  Suite *suite = suite_create("s21_is_greater");
  TCase *tcase = tcase_create("case_s21_is_greater");

  tcase_add_test(tcase, decimal_is_greater_1);
  tcase_add_test(tcase, decimal_is_greater_2);
  tcase_add_test(tcase, decimal_is_greater_3);
  tcase_add_test(tcase, decimal_is_greater_4);
  tcase_add_test(tcase, decimal_is_greater_5);
  tcase_add_test(tcase, decimal_is_greater_6);
  tcase_add_test(tcase, decimal_is_greater_7);
  tcase_add_test(tcase, decimal_is_greater_8);
  tcase_add_test(tcase, verter_is_greater_1);
  tcase_add_test(tcase, verter_is_greater_2);
  tcase_add_test(tcase, verter_is_greater_3);
  tcase_add_test(tcase, verter_is_greater_4);
  tcase_add_test(tcase, verter_is_greater_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_less_or_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_or_equal_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_or_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_or_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_or_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_or_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_or_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_less_or_equal() {
  Suite *suite = suite_create("s21_is_less_or_equal");
  TCase *tcase = tcase_create("case_s21_is_less_or_equal");

  tcase_add_test(tcase, decimal_is_less_or_equal_1);
  tcase_add_test(tcase, decimal_is_less_or_equal_2);
  tcase_add_test(tcase, decimal_is_less_or_equal_3);
  tcase_add_test(tcase, decimal_is_less_or_equal_4);
  tcase_add_test(tcase, decimal_is_less_or_equal_5);
  tcase_add_test(tcase, decimal_is_less_or_equal_6);
  tcase_add_test(tcase, decimal_is_less_or_equal_7);
  tcase_add_test(tcase, decimal_is_less_or_equal_8);
  tcase_add_test(tcase, verter_is_less_or_equal_1);
  tcase_add_test(tcase, verter_is_less_or_equal_2);
  tcase_add_test(tcase, verter_is_less_or_equal_3);
  tcase_add_test(tcase, verter_is_less_or_equal_4);
  tcase_add_test(tcase, verter_is_less_or_equal_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_less_1) {
  s21_decimal x = {{4294967295, 0, 0, 0}};
  s21_decimal y = {{0, 1, 0, 0}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 2, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_less() {
  Suite *suite = suite_create("s21_is_less");
  TCase *tcase = tcase_create("case_s21_is_less");

  tcase_add_test(tcase, decimal_is_less_1);
  tcase_add_test(tcase, decimal_is_less_2);
  tcase_add_test(tcase, decimal_is_less_3);
  tcase_add_test(tcase, decimal_is_less_4);
  tcase_add_test(tcase, decimal_is_less_5);
  tcase_add_test(tcase, decimal_is_less_6);
  tcase_add_test(tcase, decimal_is_less_7);
  tcase_add_test(tcase, decimal_is_less_8);
  tcase_add_test(tcase, verter_is_less_1);
  tcase_add_test(tcase, verter_is_less_2);
  tcase_add_test(tcase, verter_is_less_3);
  tcase_add_test(tcase, verter_is_less_4);
  tcase_add_test(tcase, verter_is_less_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(decimal_is_not_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_2) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE_DECIMAL}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_not_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE_DECIMAL}};
  s21_decimal y = {{1747, 0, 1, 0}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_not_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_not_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_not_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_not_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_not_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_not_equal() {
  Suite *suite = suite_create("s21_is_not_equal");
  TCase *tcase = tcase_create("case_s21_is_not_equal");

  tcase_add_test(tcase, decimal_is_not_equal_1);
  tcase_add_test(tcase, decimal_is_not_equal_2);
  tcase_add_test(tcase, decimal_is_not_equal_3);
  tcase_add_test(tcase, decimal_is_not_equal_4);
  tcase_add_test(tcase, decimal_is_not_equal_5);
  tcase_add_test(tcase, decimal_is_not_equal_6);
  tcase_add_test(tcase, decimal_is_not_equal_7);
  tcase_add_test(tcase, verter_is_not_equal_1);
  tcase_add_test(tcase, verter_is_not_equal_2);
  tcase_add_test(tcase, verter_is_not_equal_3);
  tcase_add_test(tcase, verter_is_not_equal_4);
  tcase_add_test(tcase, verter_is_not_equal_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(test_s21_negate_1) {
  s21_decimal num = {{1, 0, 0, 2147483648u}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal num = {{1, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_negate_3) {
  s21_decimal num = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(verter_negate_1) {
  s21_decimal x = {{32444, 100, 343253, -2145976320}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "32444 100 343253 1507328";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_negate_2) {
  s21_decimal x = {{1, 1, 1, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "1 1 1 2148401152";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_negate_3) {
  s21_decimal x = {{0, 0, 0, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "0 0 0 2148401152";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_negate() {
  Suite *suite = suite_create("s21_negate");
  TCase *tcase = tcase_create("case_s21_negate");

  tcase_add_test(tcase, test_s21_negate_1);
  tcase_add_test(tcase, test_s21_negate_2);
  tcase_add_test(tcase, test_s21_negate_3);
  tcase_add_test(tcase, verter_negate_1);
  tcase_add_test(tcase, verter_negate_2);
  tcase_add_test(tcase, verter_negate_3);

  suite_add_tcase(suite, tcase);

  return suite;
}
