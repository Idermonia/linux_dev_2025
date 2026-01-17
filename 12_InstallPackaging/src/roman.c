/**
 * @file roman.c
 * @brief Roman numeral conversion implementation
 */

#include "roman.h"
#include <string.h>

char* arabic_to_roman(int num, char* result) {
    if (num < 1 || num > 100 || result == NULL) {
        return NULL;
    }
    
    static const char* roman_table[] = {
        "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
        "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
        "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
        "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
        "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
        "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
        "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
        "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXVII", "LXXVIII", "LXXIX", "LXXX",
        "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
        "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
    };
    
    strcpy(result, roman_table[num - 1]);
    return result;
}

int roman_to_arabic(const char* roman) {
    if (roman == NULL || *roman == '\0') {
        return -1;
    }
    
    for (int i = 1; i <= 100; i++) {
        char temp[MAX_ROMAN_LEN];
        arabic_to_roman(i, temp);
        if (strcmp(roman, temp) == 0) {
            return i;
        }
    }
    
    return -1;
}
