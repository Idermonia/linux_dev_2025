/**
 * @mainpage Number Guessing Game
 * 
 * @section synopsis SYNOPSIS
 * guess [-r]
 * 
 * @section description DESCRIPTION
 * A number guessing game where the computer tries to guess a number
 * between 1 and 100 using binary search algorithm. The program asks
 * questions like "Is your number greater than X?" and narrows down
 * the range until it finds the correct number.
 * 
 * Supports both Arabic (1, 2, 3) and Roman (I, II, III) numeral modes.
 * 
 * @section options OPTIONS
 * - `-r` - Use Roman numerals instead of Arabic
 * - `-h` or `--help` - Show help message
 * 
 * @section examples EXAMPLES
 * Arabic mode:
 * @code
 * $ guess
 * Think of a number between 1 and 100. Press Enter when ready.
 * Is your number greater than 50? (Yes/No): No
 * Is your number greater than 25? (Yes/No): Yes
 * Your number is 38!
 * @endcode
 * 
 * Roman mode:
 * @code
 * $ guess -r
 * Think of a Roman number between I and C. Press Enter when ready.
 * Is your number greater than L? (Yes/No): Yes
 * Is your number greater than LXXV? (Yes/No): No
 * Your number is LXIII!
 * @endcode
 */


 /** @page guess
 * Number Guessing Game
 * @section SYNOPSIS
 * `guess` [-r for roman]
 * @section DESCRIPTION
 * Play a guessing game with arabic or roman numerals.
 *
 */

/**
 * @file guess.c
 *
 * Implementation of a number guessing game using binary search algorithm.
 * The computer tries to guess a number between 1 and 100 by asking if the
 * number is greater than its midpoint guess. Supports both Arabic and
 * Roman numeral modes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <unistd.h>

#include "roman.h"

/**
 * Macro for internationalization using gettext.
 *
 * @param STRING string to translate
 * @return translated string
 */
#define _(STRING) gettext(STRING)

/**
 * Path to locale message catalogs.
 *
 * Current directory for development, should be changed for
 * installation to standard locale directory.
 */
#ifndef LOCALEDIR
#define LOCALEDIR "/usr/local/share/locale"
#endif

/**
 * Maximum length of Roman numeral string.
 *
 * Enough space for Roman numerals up to C (100).
 */
#define MAX_ROMAN_LEN 20

/**
 * Minimum number in guessing range.
 *
 * The smallest number user can think of.
 */
#define MIN_NUMBER 1

/**
 * Maximum number in guessing range.
 *
 * The largest number user can think of.
 */
#define MAX_NUMBER 100

/** Roman numeral mode flag (0=Arabic, 1=Roman) */
static int roman_mode = 0;

/** Print number in current mode (Arabic или Roman).
 *
 * @param num number to print
 */
void print_number(int num) {
    if (roman_mode) {
        char roman[MAX_ROMAN_LEN];
        if (arabic_to_roman(num, roman)) {
            printf("%s", roman);
        }
    } else {
        printf("%d", num);
    }
}

/** Get Yes/No answer from user.
 *
 * @param prompt question to ask user
 * @param buffer buffer for user input
 * @param size buffer size
 * @return 1 for Yes, 0 for No, -1 for invalid response
 */
int get_user_answer(const char* prompt, char* buffer, size_t size) {
    printf("%s", prompt);
    
    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }
    
    buffer[strcspn(buffer, "\n")] = 0;
    
    if (strcasecmp(buffer, _("Yes")) == 0) {
        return 1;
    } else if (strcasecmp(buffer, _("No")) == 0) {
        return 0;
    } else {
        return -1;
    }
}

/** Main function implementing the guessing game.
 *
 * The game uses binary search to guess the user's number. The range is
 * repeatedly halved based on user responses until the number is found.
 *
 * Usage: guess [-r]
 *   -r    use Roman numerals
 *
 * The lower 32 bits of the seed should be thoroughly initialized.
 * A particular seed will produce the same results on all platforms.
 *
 * @param argc argument count
 * @param argv argument vector
 * @return exit status (0=success, 1=error)
 */
int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALEDIR);
    textdomain("guess");
    
    if (argc > 1) {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
            printf(_("Usage: %s [-r]\n"), argv[0]);
            printf(_("  -r    use Roman numerals\n"));
            exit(EXIT_SUCCESS);
        } else if (!strcmp(argv[1], "-r")) {
            roman_mode = 1;
        } else {
            fprintf(stderr, _("Error: Unknown option '%s'\n"), argv[1]);
            fprintf(stderr, _("Try '%s -h' for help\n"), argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    
    int low = MIN_NUMBER;
    int high = MAX_NUMBER;
    int guess;
    char response[100];
    
    if (roman_mode) {
        printf(_("Think of a Roman number between I and C. Press Enter when ready.\n"));
    } else {
        printf(_("Think of a number between 1 and 100. Press Enter when ready.\n"));
    }
    getchar();
    
    while (low <= high) {
        guess = (low + high) / 2;
        
        char prompt[100];
        if (roman_mode) {
            char roman_guess[MAX_ROMAN_LEN];
            arabic_to_roman(guess, roman_guess);
            
            char roman_next[MAX_ROMAN_LEN];
            arabic_to_roman(guess + 1, roman_next);
            
            snprintf(prompt, sizeof(prompt), 
                    _("Is your number greater than %s? (Yes/No): "), roman_guess);
        } else {
            snprintf(prompt, sizeof(prompt), 
                    _("Is your number greater than %d? (Yes/No): "), guess);
        }
        
        int answer = get_user_answer(prompt, response, sizeof(response));
        
        if (answer == -1) {
            printf(_("Error: Please answer only 'Yes' or 'No'.\n"));
            continue;
        } else if (answer == 1) {
            low = guess + 1;
        } else {
            high = guess;
        }
        
        if (low == high) {
            printf(_("Your number is "));
            print_number(low);
            printf("!\n");
            break;
        }
        
        if (low > high) {
            printf(_("Your number is "));
            print_number(guess);
            printf("!\n");
            break;
        }
    }
    
    return 0;
}
