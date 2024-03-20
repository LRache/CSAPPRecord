#include <stdio.h>

union
{
    char string[4];
    int integer;
} number_input_string;

char input_string[0x800];
FILE *infile;

char *blank_line() {}

char* skip() {
    char *v3; // rbx
    while (1) {
        int v0 = number_input_string.integer; // rax
        char *v1 = v0 * 0x50; // rdi
        v1 += (long long)input_string;
        char *v2 = fgets(v0, infile, 0x50); // rax
        v3 = v2; // rbx
        if (v2 == NULL) break;
    }
    return v3;
}


