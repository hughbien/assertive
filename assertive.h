#ifndef ASSERTIVE_H
#define ASSERTIVE_H

#define ASSERTIVE_MAX_TESTS 128
#define ASSERTIVE_MAX_STRING 1024
#define ASSERTIVE_MAX_BUFFER 10 * 1024

/* public assert functions */
#define assert_true(cond)              assert_true_(__FILE__,__LINE__,(cond))
#define assert_false(cond)             assert_false_(__FILE__,__LINE__,(cond))
#define assert_null(p)                 assert_null_(__FILE__,__LINE__,(p))
#define assert_not_null(p)             assert_not_null_(__FILE__,__LINE__,(p))
#define assert_str_equal(ex,ac)        assert_str_equal_(__FILE__,__LINE__,(p))
#define assert_str_not_equal(ex,ac)    assert_str_not_equal_(__FILE__,__LINE__,(ex),(ac))
#define assert_int_equal(ex,ac)        assert_int_equal_(__FILE__,__LINE__,(ex),(ac))
#define assert_int_not_equal(ex,ac)    assert_int_not_equal_(__FILE__,__LINE__,(ex),(ac))
#define assert_dbl_equal(ex,ac,dt)     assert_dbl_equal_(__FILE__,__LINE__,(ex),(ac),(dt))
#define assert_dbl_not_equal(ex,ac,dt) assert_dbl_not_equal_(__FILE__,__LINE__,(ex),(ac),(dt))
#define assert_ptr_equal(ex,ac)        assert_ptr_equal_(__FILE__,__LINE__,(ex),(ac))
#define assert_ptr_not_equal(ex,ac)    assert_ptr_not_equal_(__FILE__,__LINE__,(ex),(ac))
#define assert_add(fn)                 assert_add_((fn),(#fn))

/* public functions */
int assert_run(int argc, char *argv[]);
void assert_fail(const char *file, int line, const char *format, ...);

/* internal assert functions */
void assert_true_(const char *file, int line, int cond);
void assert_false_(const char *file, int line, int cond);
void assert_null_(const char *file, int line, void *pointer);
void assert_not_null_(const char *file, int line, void *pointer);
void assert_str_equal_(const char *file, int line, const char *ex, const char *ac);
void assert_str_not_equal_(const char *file, int line, const char *ex, const char *ac);
void assert_int_equal_(const char *file, int line, int ex, int ac);
void assert_int_not_equal_(const char *file, int line, int ex, int ac);
void assert_dbl_equal_(const char *file, int line, double ex, double ac, double delta);
void assert_dbl_not_equal_(const char *file, int line, double ex, double ac, double delta);
void assert_ptr_equal_(const char *file, int line, void *ex, void *ac);
void assert_ptr_not_equal_(const char *file, int line, void *ex, void *ac);
void assert_add_(void (*fn)(), const char *name);

#endif /* ASSERTIVE_H */
