#ifndef ASSERTIVE_H
#define ASSERTIVE_H

#define ASSERTIVE_MAX_TESTS 128
#define ASSERTIVE_MAX_STRING 1024
#define ASSERTIVE_MAX_BUFFER 10 * 1024

/* public assert functions */
#define assert_true(cond)              if(!assert_true_(__FILE__,__LINE__,(cond))) return
#define assert_false(cond)             if(!assert_false_(__FILE__,__LINE__,(cond))) return
#define assert_null(p)                 if(!assert_null_(__FILE__,__LINE__,(p))) return
#define assert_not_null(p)             if(!assert_not_null_(__FILE__,__LINE__,(p))) return
#define assert_str_equal(ex,ac)        if(!assert_str_equal_(__FILE__,__LINE__,(p))) return
#define assert_str_not_equal(ex,ac)    if(!assert_str_not_equal_(__FILE__,__LINE__,(ex),(ac))) return
#define assert_int_equal(ex,ac)        if(!assert_int_equal_(__FILE__,__LINE__,(ex),(ac))) return
#define assert_int_not_equal(ex,ac)    if(!assert_int_not_equal_(__FILE__,__LINE__,(ex),(ac))) return
#define assert_dbl_equal(ex,ac,dt)     if(!assert_dbl_equal_(__FILE__,__LINE__,(ex),(ac),(dt))) return
#define assert_dbl_not_equal(ex,ac,dt) if(!assert_dbl_not_equal_(__FILE__,__LINE__,(ex),(ac),(dt))) return
#define assert_ptr_equal(ex,ac)        if(!assert_ptr_equal_(__FILE__,__LINE__,(ex),(ac))) return
#define assert_ptr_not_equal(ex,ac)    if(!assert_ptr_not_equal_(__FILE__,__LINE__,(ex),(ac))) return
#define assert_add(fn)                 assert_add_((fn),(#fn))

/* public functions */
int assert_run(int argc, char *argv[]);
void assert_fail(const char *file, int line, const char *message);

/* internal assert functions */
int assert_true_(const char *file, int line, int cond);
int assert_false_(const char *file, int line, int cond);
int assert_null_(const char *file, int line, void *pointer);
int assert_not_null_(const char *file, int line, void *pointer);
int assert_str_equal_(const char *file, int line, const char *ex, const char *ac);
int assert_str_not_equal_(const char *file, int line, const char *ex, const char *ac);
int assert_int_equal_(const char *file, int line, int ex, int ac);
int assert_int_not_equal_(const char *file, int line, int ex, int ac);
int assert_dbl_equal_(const char *file, int line, double ex, double ac, double delta);
int assert_dbl_not_equal_(const char *file, int line, double ex, double ac, double delta);
int assert_ptr_equal_(const char *file, int line, void *ex, void *ac);
int assert_ptr_not_equal_(const char *file, int line, void *ex, void *ac);
void assert_add_(void (*fn)(), const char *name);

#endif /* ASSERTIVE_H */
