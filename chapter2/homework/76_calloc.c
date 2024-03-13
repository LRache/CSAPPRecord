#include <stdlib.h>
#include <string.h>

void *my_calloc(size_t nmemb, size_t size) {
    if (nmemb == 0) return NULL;
    if (size == 0) return NULL;
    size_t t = nmemb * size;
    if (t / size != nmemb) return NULL;
    void *ptr = malloc(t);
    memset(ptr, 0, t);
    return ptr;
}