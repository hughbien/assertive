#include <assert.h>
#include <math.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "assertive.h"

static void (*assert_test_fns[ASSERTIVE_MAX_TESTS])();
static const char *assert_test_names[ASSERTIVE_MAX_TESTS];
static int assert_test_flags[ASSERTIVE_MAX_TESTS];
static int assert_test_count = 0;
static int assert_test_index = 0;
static char assert_test_buffer[ASSERTIVE_MAX_BUFFER];
static jmp_buf assert_test_jump;

static int assert_test_continue(int argc, char *argv[], const char *name) {
  if (argc == 1) { return 0; }
  int index;
  for (index = 0; index < argc; index++) {
    if (strcmp(name, argv[index]) == 0) { return 0; }
  }
  return 1;
}

static int assert_test_list(char *argv[]) {
  if (strcmp(argv[1], "--tests") == 0 || strcmp(argv[1], "-t") == 0) {
    int index = 0;
    while (index < assert_test_count) {
      printf("%s\n", assert_test_names[index]);
      index++;
    }
    return 1;
  }
  return 0;
}

static int assert_test_help(char *argv[]) {
  if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
    printf("Usage: %s [test,]\nOptions:\n", argv[0]);
    printf("  -t  --tests    list all tests\n");
    return 1;
  }
  return 0;
}

void assert_add_(void (*fn)(), const char *name) {
  assert(assert_test_count < ASSERTIVE_MAX_TESTS);
  assert_test_fns[assert_test_count] = fn;
  assert_test_names[assert_test_count] = name;
  assert_test_count++;
}

int assert_run(int argc, char *argv[]) {
  int passes = 0;
  int fails = 0;
  
  if (argc == 2 && assert_test_list(argv)) {
    return 0;
  } else if (argc == 2 && assert_test_help(argv)) {
    return 0;
  }

  assert_test_index = 0;
  while (assert_test_index < assert_test_count) {
    if (assert_test_continue(argc, argv, assert_test_names[assert_test_index])) {
      assert_test_index++;
      continue;
    }
    assert_test_flags[assert_test_index] = 0;
    if (!setjmp(assert_test_jump)) {
      assert_test_fns[assert_test_index]();
    }
    if (assert_test_flags[assert_test_index]) {
      printf("F");
      fails++;
    } else {
      printf(".");
      passes++;
    }
    assert_test_index++;
  }

  if (fails > 0) {
    printf("\n\n%s\nPasses: %d, Fails: %d\n", assert_test_buffer, passes, fails);
    return 0;
  } else {
    printf("\n\nOK (%d tests)\n", passes);
    return 1;
  }
}

void assert_fail(const char *file, int line, const char *format, ...) {
  va_list args;
  char message[ASSERTIVE_MAX_STRING];
  char temp[ASSERTIVE_MAX_STRING];
  int index, fails = 0;
  for (index = 0; index < assert_test_index; index++) {
    if (assert_test_flags[index]) { fails++; }
  }
  va_start(args, format);
  vsnprintf(message, ASSERTIVE_MAX_STRING, format, args);
  va_end(args);
  snprintf(temp, ASSERTIVE_MAX_STRING, "%d) %s@%s:%d %s\n", 
      fails + 1,
      assert_test_names[assert_test_index],
      file,
      line,
      message);
  assert(strlen(assert_test_buffer) + strlen(temp) < ASSERTIVE_MAX_BUFFER);
  strcat(assert_test_buffer, temp);
  assert_test_flags[assert_test_index] = 1;
  longjmp(assert_test_jump, 1);
}

void assert_true_(const char *file, int line, int cond) {
  if (!cond) {
    assert_fail(file, line, "Expected <true> but was <%d>", cond);
  }
}

void assert_false_(const char *file, int line, int cond) {
  if (cond) {
    assert_fail(file, line, "Expected <false> but was <%d>", cond);
  }
}

void assert_null_(const char *file, int line, void *pointer) {
  if (pointer != NULL) {
    assert_fail(file, line, "Expected <null> but was not");
  }
}

void assert_not_null_(const char *file, int line, void *pointer) {
  if (pointer == NULL) {
    assert_fail(file, line, "Expected not <null> but was");
  }
}

void assert_str_equal_(const char *file, int line, char *ex, char *ac) {
  if (strcmp(ex, ac) != 0) {
    assert_fail(file, line, "Expected <\"%s\"> but was <\"%s\">", ex, ac);
  }
}

void assert_str_not_equal_(const char *file, int line, char *ex, char *ac) {
  if (strcmp(ex, ac) == 0) {
    assert_fail(file, line, "Expected not <\"%s\"> but was", ex);
  }
}

void assert_int_equal_(const char *file, int line, int ex, int ac) {
  if (ex != ac) {
    assert_fail(file, line, "Expected <%d> but was <%d>", ex, ac);
  }
}

void assert_int_not_equal_(const char *file, int line, int ex, int ac) {
  if (ex == ac) {
    assert_fail(file, line, "Expected not <%d> but was", ex);
  }
}

void assert_dbl_equal_(const char *file, int line, double ex, double ac, double dt) {
  if (fabs(ex - ac) > dt) {
    assert_fail(file, line, "Expected <%g> but was <%g>", ex, ac);
  }
}

void assert_dbl_not_equal_(const char *file, int line, double ex, double ac, double dt) {
  if (fabs(ex - ac) <= dt) {
    assert_fail(file, line, "Expected not <%g> but was", ex);
  }
}

void assert_ptr_equal_(const char *file, int line, void *ex, void *ac) {
  if (ex != ac) {
    assert_fail(file, line, "Expected <%p> but was <%p>", ex, ac);
  }
}

void assert_ptr_not_equal_(const char *file, int line, void *ex, void *ac) {
  if (ex == ac) {
    assert_fail(file, line, "Expected not <%p> but was", ex);
  }
}
