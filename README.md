Description
===========

Assertive is an incomplete unit test library for C.

Install
=======

Copy `assertive.h` and `assertive.c` to your project.

Optionally, you can create a static library for all your projects:

    % make libassertive.a
    % cp libassertive.a /usr/local/lib/.
    % cp assertive.h /usr/local/include/.
    % cd path/to/project
    % gcc -I/usr/local/include -L/usr/local/lib -lassertive *.c

Usage
=====

Here's an example test file:

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

    1) test_str@example.c:9 Expected <"expected"> but was <"actual">

    Passes: 1, Fails: 1

You can pass any number of test names to run focused tests also:

    % a.out test_addition
    .

    OK (1 tests)

You can write your own assertions.  Implement a function which takes a filename
and line number as its first two parameters.  Call `assert_fail` if your
assertion fails.  Create a macro so you don't have to manually pass in the
`file` and `line` parameters.

    #define assert_is_99(i) assert_is_99_(__FILE__,__LINE__,(i))

    void assert_is_99_(const char *file, int line, int myint) {
      if (myint != 99) {
        assert_fail(file, line, "Expected <99> but was <%d>", myint);
      }
    }

    void test_something {
      assert_is_99(99);  // passes
      assert_is_99(100); // fails
    }

TODO
====

* regex support
* add zsh autocompletion file
* add vim quickfix config

License
=======

Copyright 2011 Hugh Bien - http://hughbien.com.
Released under MIT License, see LICENSE.md for more info.
