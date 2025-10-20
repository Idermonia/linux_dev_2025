#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 10
#define MAX_SUB_LEN 1024

void process_substitution(const char *string, const char *sub, char *result, regmatch_t *matches, int num_matches) {
    char *dest = result;
    const char *src = sub;
    
    while (*src) {
        if (*src == '\\') {
            src++;
            if (*src == '\\') {
                *dest++ = '\\';
                src++;
            } else if (*src >= '0' && *src <= '9') {
                int match_num = *src - '0';
                src++;
                
                if (match_num >= num_matches) {
                    fprintf(stderr, "No group %d\n", match_num);
                    exit(1);
                }
                
                if (matches[match_num].rm_so != -1) {
                    int match_len = matches[match_num].rm_eo - matches[match_num].rm_so;
                    strncpy(dest, string + matches[match_num].rm_so, match_len);
                    dest += match_len;
                }
            } else {
                *dest++ = '\\';
                if (*src) *dest++ = *src++;
            }
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s regexp substitution string\n", argv[0]);
        return 1;
    }
    
    const char *regexp = argv[1];
    const char *substitution = argv[2];
    const char *string = argv[3];
    
    regex_t regex;
    int ret;
    
    ret = regcomp(&regex, regexp, REG_EXTENDED);
    if (ret != 0) {
        char error_buf[100];
        regerror(ret, &regex, error_buf, sizeof(error_buf));
        fprintf(stderr, "Regex error: %s\n", error_buf);
        return 1;
    }
    
    regmatch_t matches[MAX_MATCHES];
    ret = regexec(&regex, string, MAX_MATCHES, matches, 0);
    
    if (ret == REG_NOMATCH) {
        printf("%s\n", string);
        regfree(&regex);
        return 0;
    } else if (ret != 0) {
        char error_buf[100];
        regerror(ret, &regex, error_buf, sizeof(error_buf));
        fprintf(stderr, "Regex execution error: %s\n", error_buf);
        regfree(&regex);
        return 1;
    }
    
    char result[MAX_SUB_LEN];
    
    if (matches[0].rm_so == 0 && matches[0].rm_eo == (int)strlen(string)) {
        process_substitution(string, substitution, result, matches, MAX_MATCHES);
        printf("%s\n", result);
    } else {
        int before_len = matches[0].rm_so;
        int after_start = matches[0].rm_eo;
        int after_len = strlen(string) - after_start;
        
        if (before_len > 0) {
            strncpy(result, string, before_len);
            result[before_len] = '\0';
        } else {
            result[0] = '\0';
        }
        
        char sub_result[MAX_SUB_LEN];
        process_substitution(string, substitution, sub_result, matches, MAX_MATCHES);
        strcat(result, sub_result);
        
        if (after_len > 0) {
            strcat(result, string + after_start);
        }
        
        printf("%s\n", result);
    }
    
    regfree(&regex);
    return 0;
}
