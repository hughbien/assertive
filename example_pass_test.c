#include <stdio.h>
#include "assertive.h"

void test_truth_pass() {
  assert_true(1);
}

void test_false_pass() {
  assert_false(0);
}

void test_null_pass() {
  assert_null(NULL);
}

void test_not_null_pass() {
  int x = 1;
  assert_not_null(&x);
}

void test_str_equal_pass() {
  assert_str_equal("lorem", "lorem");
}

void test_str_not_equal_pass() {
  assert_str_not_equal("lorem", "ipsum");
}

void test_int_equal_pass() {
  assert_int_equal(1, 1);
}

void test_int_not_equal_pass() {
  assert_int_not_equal(1, -1);
}

void test_dbl_equal_pass() {
  assert_dbl_equal(1.0, 1.05, 0.1);
}

void test_dbl_not_equal_pass() {
  assert_dbl_not_equal(1.0, 1.15, 0.1);
}

void test_ptr_equal_pass() {
  int x = 1;
  int *p1 = &x, *p2 = &x;
  assert_ptr_equal(p1, p2);
}

void test_ptr_not_equal_pass() {
  int x = 1, y = 2;
  int *p1 = &x, *p2 = &y;
  assert_ptr_not_equal(p1, p2);
}

void add_example_pass_tests() {
  assert_add(test_truth_pass);
  assert_add(test_false_pass);
  assert_add(test_null_pass);
  assert_add(test_not_null_pass);
  assert_add(test_str_equal_pass);
  assert_add(test_str_not_equal_pass);
  assert_add(test_int_equal_pass);
  assert_add(test_int_not_equal_pass);
  assert_add(test_dbl_equal_pass);
  assert_add(test_dbl_not_equal_pass);
  assert_add(test_ptr_equal_pass);
  assert_add(test_ptr_not_equal_pass);
}
