Description
===========

Assertive is an incomplete unit test library for C.

Usage
=====

Just two files are required: `assertive.h` and `assertive.c`.  Here's an
example test file:

    #include <stdio.h>
    #incldue "assertive.h"

    void test_addition() {
      assert_int_equal(2, 1+1);
    }

    void test_str() {
      assert_str_equal("expected", "actual");
    }

    int main(int argc, char *argv[]) {
      assert_add(test_addition);
      assert_add(test_str);
      return assert_run(argc, argv);
    }

Then on the command line:

    % gcc *.c
    % a.out
    .F

    1) test_str_fail:9 Expected <"expected"> but was <"actual">

    Passes: 1, Fails: 1

You can pass any number of test names to run focused tests also:

    % a.out test_addition
    ..

    OK (1 tests)

TODO
====

* implement assertions
* faster test discovery
* add a `--tests` option to list all tests
* add zsh autocompletion file
* add vim quickfix config
* better examples

License
=======

Copyright 2011 Hugh Bien - http://hughbien.com.
Released under MIT License, see LICENSE.md for more info.
