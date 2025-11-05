#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <rhash.h>

#include "config.h" 

#if USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

void print_usage() {
    fprintf(stderr, "Usage: <algorithm> <file_or_string>\n");
    fprintf(stderr, "Algorithms: MD5, SHA1, TTH (hex) or md5, sha1, tth (base64)\n");
}

void compute_hash(const char* algo_name, const char* data, int is_file) {
    int algorithm;
    int hash_size;
    
    if (strcasecmp(algo_name, "md5") == 0 || strcasecmp(algo_name, "MD5") == 0) {
        algorithm = RHASH_MD5;
        hash_size = rhash_get_digest_size(algorithm);
    } else if (strcasecmp(algo_name, "sha1") == 0 || strcasecmp(algo_name, "SHA1") == 0) {
        algorithm = RHASH_SHA1;
        hash_size = rhash_get_digest_size(algorithm);
    } else if (strcasecmp(algo_name, "tth") == 0 || strcasecmp(algo_name, "TTH") == 0) {
        algorithm = RHASH_TTH;
        hash_size = rhash_get_digest_size(algorithm);
    } else {
        fprintf(stderr, "NOT an algorithm >:( -> %s\n", algo_name);
        return;
    }
    
    unsigned char hash[64];
    char output[130];
    int result;
    
    if (is_file) {
        result = rhash_file(algorithm, data, hash);
    } else {
        result = rhash_msg(algorithm, data, strlen(data), hash);
    }
    
    if (result < 0) {
        fprintf(stderr, "Error computing hash\n");
        return;
    }
    
    int flags = (algo_name[0] >= 'A' && algo_name[0] <= 'Z') ? RHPR_HEX : RHPR_BASE64;
    
    if (rhash_print_bytes(output, hash, hash_size, flags) < 0) {
        fprintf(stderr, "Error formatting hash\n");
        return;
    }
    
    printf("%s\n", output);
}

int main() {
    rhash_library_init();
    
    char *line = NULL;
    size_t len = 0;                                 
    ssize_t read;

    while (1) {
#if USE_READLINE
        line = readline("");
        if (!line) break;
        if (strlen(line) == 0) {
            free(line);
            continue;
        }
        
        add_history(line);
#else
        
        read = getline(&line, &len, stdin);
        if (read == -1) break;
        
        if (read > 0 && line[read-1] == '\n') {
            line[read-1] = '\0';
        }
        if (strlen(line) == 0) {
            continue;
        }
#endif

        char *line_copy = strdup(line);
        char *algo = strtok(line_copy, " \t");
        char *target = strtok(NULL, " \t");
        
        if (!algo || !target) {
            print_usage();
            free(line_copy);
#if USE_READLINE
            free(line);
            line = NULL;
#endif
            continue;
        }
        
        int is_file = 1;
        if (target[0] == '"') {
            is_file = 0;
            target++; 
            
            char *closing_quote = strchr(target, '"');
            if (closing_quote) {
                *closing_quote = '\0';
            }
        }
        
        compute_hash(algo, target, is_file);
        
        free(line_copy);
#if USE_READLINE
        free(line);
        line = NULL;
#endif
    }
    
    free(line);
    return 0;
}
