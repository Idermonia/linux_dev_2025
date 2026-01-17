#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "roman.h"

START_TEST(test_arabic_to_roman_basic)
{
    char result[MAX_ROMAN_LEN];
    ck_assert(arabic_to_roman(1, result) != NULL);
    ck_assert_str_eq(result, "I");
    ck_assert(arabic_to_roman(5, result) != NULL);
    ck_assert_str_eq(result, "V");
    ck_assert(arabic_to_roman(10, result) != NULL);
    ck_assert_str_eq(result, "X");
}
END_TEST

START_TEST(test_roman_to_arabic_basic)
{
    ck_assert_int_eq(roman_to_arabic("I"), 1);
    ck_assert_int_eq(roman_to_arabic("V"), 5);
    ck_assert_int_eq(roman_to_arabic("X"), 10);
}
END_TEST

START_TEST(test_multiple_conversions)
{
    char result[MAX_ROMAN_LEN];
    struct {
        int arabic;
        const char *roman;
    } tests[] = {
        {2, "II"},
        {3, "III"},
        {4, "IV"},
        {9, "IX"},
        {42, "XLII"},
        {99, "XCIX"},
        {0, NULL}
    };
    for (int i = 0; tests[i].arabic > 0; i++) {
        ck_assert(arabic_to_roman(tests[i].arabic, result) != NULL);
        ck_assert_str_eq(result, tests[i].roman);
        ck_assert_int_eq(roman_to_arabic(tests[i].roman), tests[i].arabic);
    }
}
END_TEST

int find_number(int secret, int min, int max) {
    int low = min;
    int high = max;
    
    while (low < high) {
        int guess = (low + high) / 2;
        
        if (secret > guess) {
            low = guess + 1;
        } else {
            high = guess;
        }
    }
    
    return low;
}

START_TEST(test_find_number)
{
    ck_assert_int_eq(find_number(50, 1, 100), 50);
    ck_assert_int_eq(find_number(1, 1, 100), 1);
    ck_assert_int_eq(find_number(100, 1, 100), 100);
    ck_assert_int_eq(find_number(75, 1, 100), 75);
}
END_TEST

START_TEST(test_find_small_range)
{
    for (int secret = 1; secret <= 10; secret++) {
        int found = find_number(secret, 1, 10);
        ck_assert_int_eq(found, secret);
    }
}
END_TEST

START_TEST(test_find_min_max)
{
    ck_assert_int_eq(find_number(1, 1, 1), 1);
    ck_assert_int_eq(find_number(1, 1, 2), 1);
    ck_assert_int_eq(find_number(2, 1, 2), 2);
}
END_TEST

START_TEST(test_find_middle)
{
    int secret = 42;
    int found = find_number(secret, 1, 100);
    ck_assert_int_eq(found, secret);
}
END_TEST

START_TEST(test_roman_in_game)
{
    char roman[20];
    int game_numbers[] = {1, 5, 10, 25, 50, 75, 100};
    const char* expected[] = {"I", "V", "X", "XXV", "L", "LXXV", "C"};
    for (int i = 0; i < 7; i++) {
        ck_assert(arabic_to_roman(game_numbers[i], roman) != NULL);
        ck_assert_str_eq(roman, expected[i]);
    }
}
END_TEST

Suite *all_suite(void)
{
    Suite *s;
    TCase *tc_roman;
    TCase *tc_game;
    s = suite_create("All");
    tc_roman = tcase_create("Roman");
    tcase_add_test(tc_roman, test_arabic_to_roman_basic);
    tcase_add_test(tc_roman, test_roman_to_arabic_basic);
    tcase_add_test(tc_roman, test_multiple_conversions);
    suite_add_tcase(s, tc_roman);
    tc_game = tcase_create("Game");
    tcase_add_test(tc_game, test_find_number);
    tcase_add_test(tc_game, test_find_small_range);
    tcase_add_test(tc_game, test_find_min_max);
    tcase_add_test(tc_game, test_find_middle);
    tcase_add_test(tc_game, test_roman_in_game);
    suite_add_tcase(s, tc_game);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;
    s = all_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
