#include <stdio.h>
#include "assertive.h"

void add_example_pass_tests();
void add_example_fail_tests();

int main(int argc, char *argv[]) {
  add_example_pass_tests();
  add_example_fail_tests();
  return assert_run(argc, argv);
}
