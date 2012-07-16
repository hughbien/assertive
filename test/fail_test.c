#include <stdio.h>
#include "assertive.h"

void test_truth_fail() {
  assert_true(0);
}

void test_false_fail() {
  assert_false(1);
}

void test_null_fail() {
  int x = 1;
  assert_null(&x);
}

void test_not_null_fail() {
  assert_not_null(NULL);
}

void test_str_equal_fail() {
  assert_str_equal("lorem", "ipsum");
}

void test_str_not_equal_fail() {
  assert_str_not_equal("lorem", "lorem");
}

void test_int_equal_fail() {
  assert_int_equal(1, -1);
}

void test_int_not_equal_fail() {
  assert_int_not_equal(1, 1);
}

void test_dbl_equal_fail() {
  assert_dbl_equal(1.0, 1.15, 0.1);
}

void test_dbl_not_equal_fail() {
  assert_dbl_not_equal(1.0, 1.05, 0.1);
}

void test_ptr_equal_fail() {
  int x = 1, y = 2;
  int *p1 = &x, *p2 = &y;
  assert_ptr_equal(p1, p2);
}

void test_ptr_not_equal_fail() {
  int x = 1;
  int *p1 = &x, *p2 = &x;
  assert_ptr_not_equal(p1, p2);
}

void add_example_fail_tests() {
  assert_add(test_truth_fail);
  assert_add(test_false_fail);
  assert_add(test_null_fail);
  assert_add(test_not_null_fail);
  assert_add(test_str_equal_fail);
  assert_add(test_str_not_equal_fail);
  assert_add(test_int_equal_fail);
  assert_add(test_int_not_equal_fail);
  assert_add(test_dbl_equal_fail);
  assert_add(test_dbl_not_equal_fail);
  assert_add(test_ptr_equal_fail);
  assert_add(test_ptr_not_equal_fail);
}
