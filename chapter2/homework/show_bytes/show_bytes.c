#include "show_bytes.h"

#include <stdio.h>
void show_bytes(bytePtr start, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%.2x", start[i]);
    }
}
