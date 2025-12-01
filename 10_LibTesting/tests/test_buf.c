#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "../src/buf.h"

// Макросы для совместимости со старыми версиями Check
#ifndef ck_assert_float_eq
#define ck_assert_float_eq(a, b, epsilon) \
    ck_assert(fabs((a) - (b)) <= (epsilon))
#endif

#ifndef ck_assert_ptr_null
#define ck_assert_ptr_null(ptr) ck_assert_ptr_eq(ptr, NULL)
#endif

#ifndef ck_assert_ptr_nonnull
#define ck_assert_ptr_nonnull(ptr) ck_assert_ptr_ne(ptr, NULL)
#endif

START_TEST(test_basic_operations)
{
    float *a = 0;
    
    ck_assert_int_eq(buf_capacity(a), 0);
    ck_assert_int_eq(buf_size(a), 0);
    
    buf_push(a, 1.3f);
    ck_assert_int_eq(buf_size(a), 1);
    ck_assert_float_eq(a[0], 1.3f, 0.0001f);
    
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_nonnull(a);
    
    buf_free(a);
    ck_assert_ptr_null(a);
}
END_TEST

START_TEST(test_push_pop)
{
    float *a = 0;
    
    buf_push(a, 1.1f);
    buf_push(a, 1.2f);
    buf_push(a, 1.3f);
    buf_push(a, 1.4f);
    
    ck_assert_int_eq(buf_size(a), 4);
    ck_assert_float_eq(buf_pop(a), 1.4f, 0.0001f);
    
    buf_trunc(a, 3);
    ck_assert_int_eq(buf_size(a), 3);
    
    ck_assert_float_eq(buf_pop(a), 1.3f, 0.0001f);
    ck_assert_float_eq(buf_pop(a), 1.2f, 0.0001f);
    ck_assert_float_eq(buf_pop(a), 1.1f, 0.0001f);
    ck_assert_int_eq(buf_size(a), 0);
    
    buf_free(a);
}
END_TEST

START_TEST(test_grow_trunc)
{
    long *ai = 0;
    
    buf_grow(ai, 1000);
    ck_assert_int_eq(buf_capacity(ai), 1000);
    ck_assert_int_eq(buf_size(ai), 0);
    
    buf_trunc(ai, 100);
    ck_assert_int_eq(buf_capacity(ai), 100);
    
    buf_free(ai);
}
END_TEST

START_TEST(test_many_elements)
{
    long *ai = 0;
    int match = 0;
    
    for (int i = 0; i < 10000; i++) {
        buf_push(ai, i);
    }
    
    ck_assert_int_eq(buf_size(ai), 10000);
    
    for (int i = 0; i < 10000; i++) {
        if (ai[i] == i) match++;
    }
    
    ck_assert_int_eq(match, 10000);
    
    buf_free(ai);
}
END_TEST

START_TEST(test_clear_empty)
{
    float *a = 0;
    
    /* Clearing NULL pointer should be no-op */
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_null(a);
}
END_TEST

Suite *buf_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Buffer");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_basic_operations);
    tcase_add_test(tc_core, test_push_pop);
    tcase_add_test(tc_core, test_grow_trunc);
    tcase_add_test(tc_core, test_many_elements);
    tcase_add_test(tc_core, test_clear_empty);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = buf_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
