/**
 * @file roman.h
 * @brief Roman numeral conversion utilities
 */

#define MAX_ROMAN_LEN 20

/**
 * @brief Convert Arabic number to Roman numeral
 * @param num Arabic number (1-100)
 * @param result Buffer for Roman numeral (must be at least MAX_ROMAN_LEN)
 * @return Pointer to result buffer, NULL on error
 */
char* arabic_to_roman(int num, char* result);

/**
 * @brief Convert Roman numeral to Arabic number
 * @param roman Roman numeral string
 * @return Arabic number (1-100), -1 on error
 */
int roman_to_arabic(const char* roman);
