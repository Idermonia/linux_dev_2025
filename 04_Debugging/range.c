#include <stdio.h>
#include <stdlib.h>

void print_help() {
    printf("Usage: range [M] N [S]\n");
    printf("Arguments:\n");
    printf("  N           - Generate [0, 1, ... N-1]\n");
    printf("  M N         - Generate [M, M+1, ... N-1]\n");
    printf("  M N S       - Generate [M, M+S, M+2S, ... N-1]\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }

    long start, end, step;
    
    if (argc == 2) {
        start = 0;
        end = atol(argv[1]);
        step = 1;
    } else if (argc == 3) {
        start = atol(argv[1]);
        end = atol(argv[2]);
        step = 1;
    } else if (argc == 4) {
        start = atol(argv[1]);
        end = atol(argv[2]);
        step = atol(argv[3]);
	if (step == 0) {
	    fprintf(stderr,"Zero step not allowed >:(\n");
            return 1;
        }
    } else {    
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }
    
    if (step > 0) {
        for (long i = start; i < end; i += step) {
            printf("%ld\n", i);
        }
    } else {
        for (long i = start; i > end; i += step) {
            printf("%ld\n", i);
        }
    }
    
    return 0;
}
