#include <stdio.h>
#include <string.h>
#include "assertive.h"

static void (*assert_test_fns[ASSERTIVE_MAX_TESTS])();
static const char *assert_test_names[ASSERTIVE_MAX_TESTS];
static int assert_test_count = 0;
static int assert_test_index = 0;
static int assert_test_failed = 0;
static int assert_test_passes = 0;
static int assert_test_fails = 0;
static char assert_test_buffer[ASSERTIVE_MAX_BUFFER];

static int assert_test_continue(int argc, char *argv[], const char *name) {
  if (argc == 1) { return 0; }
  int index;
  for (index = 0; index < argc; index++) {
    if (strcmp(name, argv[index]) == 0) { return 0; }
  }
  return 1;
}

void assert_add_(void (*fn)(), const char *name) {
  assert_test_fns[assert_test_count] = fn;
  assert_test_names[assert_test_count] = name;
  assert_test_count++;
}

int assert_run(int argc, char *argv[]) {
  for (assert_test_index = 0; assert_test_index < assert_test_count; assert_test_index++) {
    if (assert_test_continue(argc, argv, assert_test_names[assert_test_index])) {
      continue;
    }
    assert_test_failed = 0;
    assert_test_fns[assert_test_index]();
    if (assert_test_failed) {
      printf("F");
      assert_test_fails++;
    } else {
      printf(".");
      assert_test_passes++;
    }
  }

  if (assert_test_fails > 0) {
    printf("\n\n%s\nPasses: %d, Fails: %d\n",
        assert_test_buffer, assert_test_passes, assert_test_fails);
    return 0;
  } else {
    printf("\n\nOK (%d tests)\n", assert_test_passes);
    return 1;
  }
}

void assert_fail(const char *file, int line, const char *message) {
  char temp[ASSERTIVE_MAX_STRING];
  snprintf(temp, ASSERTIVE_MAX_STRING, "%d) %s@%s:%d %s\n", 
      assert_test_fails + 1,
      assert_test_names[assert_test_index],
      file,
      line,
      message);
  strcat(assert_test_buffer, temp);
  assert_test_failed = 1;
}

int assert_true_(const char *file, int line, int cond) {
  if (!cond) {
    assert_fail(file, line, "Expected true but was not");
  }
  return cond;
}

int assert_false_(const char *file, int line, int cond) {
  if (cond) {
    assert_fail(file, line, "Expected false but was true");
  }
  return !cond;
}
