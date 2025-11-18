#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALE_PATH);       
    textdomain("guess");

    int low = 1;
    int high = 100;
    int guess;
    char response[10];
    
    printf(_("Think of a number between 1 and 100. Press Enter when ready.\n"));
    getchar();
    
    while (low <= high) {
        guess = (low + high) / 2;
        
        printf(_("Is your number greater than %d? (Yes/No): "), guess);
        
        if (fgets(response, sizeof(response), stdin) == NULL) {
            printf("\n");
            printf(_("Error: Input closed unexpectedly.\n"));
            return 1;
        }
        
        response[strcspn(response, "\n")] = 0;
        
        if (strcasecmp(response, _("Yes")) == 0) {
            low = guess + 1;
        } else if (strcasecmp(response, _("No")) == 0) {
            high = guess;
        } else {
            printf(_("Error: Please answer only 'Yes' or 'No'.\n"));
            continue;
        }
        
        if (low == high) {
            printf(_("Your number is %d!\n"), low);
            break;
        }

        if (low > high) {
            printf(_("Your number is %d!\n"), guess);
            break;
        }
    }
    
    return 0;
}
