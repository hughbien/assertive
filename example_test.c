#include <stdio.h>
#include "assertive.h"

void test_truth_pass() {
  assert_true(1);
}

void test_truth_fail() {
  assert_true(0);
}

void test_false_pass() {
  assert_false(0);
}

void test_false_fail() {
  assert_false(1);
}

void test_null_pass() {
  assert_null(NULL);
}

void test_null_fail() {
  int x = 1;
  assert_null(&x);
}

int main(int argc, char *argv[]) {
  assert_add(test_truth_pass);
  assert_add(test_truth_fail);
  assert_add(test_false_pass);
  assert_add(test_false_fail);
  assert_add(test_null_pass);
  assert_add(test_null_fail);
  assert_run(argc, argv);
  return 0;
}
