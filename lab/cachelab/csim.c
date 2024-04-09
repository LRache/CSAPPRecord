#include "cachelab.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <getopt.h>
#include <string.h>
#include <assert.h>

typedef struct
{
    int valid;
    uint32_t tag;
    int stamp;
} CacheLine;

CacheLine **cache;
int s, E, b = 2;
uint64_t S;
FILE *traceFile;
int verboseFlag = 0;
int stamp = 0;
int missCount = 0, hitCount = 0, evictionCount = 0;

void init_cache() {
    cache = (CacheLine**)malloc(sizeof(CacheLine*) * S);
    for (int i = 0; i < S; i++)
    {
        cache[i] = (CacheLine*)malloc(sizeof(CacheLine) * E);
    }
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < E; j++) {
            cache[i][j].valid = 0;
            cache[i][j].tag = 0;
            cache[i][j].stamp = 0;
        }
    }
}

void free_cache() {
    for (int i = 0; i < S; i++) {
        free(cache[i]);
        cache = NULL;
    }
    free(cache);
}

void phase_argv(int argc, char **argv) {
    int opt;
    char tracefp[80];
    while ((opt = getopt(argc, argv, "hvs:E:b:t:V")) != -1) {
        switch (opt)
        {
        case 's':
            sscanf(optarg, "%d", &s);
            S = 1 << s;
            break;
        case 'E':
            sscanf(optarg, "%d", &E);
            break;
        case 'b':
            sscanf(optarg, "%d", &b);
            break;
        case 't':
            strncpy(tracefp, optarg, 80);
            break;
        case 'V':
            verboseFlag = 1;
            break;
        default:
            break;
        }
    }
    traceFile = fopen(tracefp, "r"); 
    assert(traceFile);
}

void verbose(const char *output) {
    if (verboseFlag) {
        printf("%s", output);
    }
}

int cache_hit(uint64_t tag, uint64_t set) {
    stamp++;
    CacheLine *lines = cache[set];
    for (int i = 0; i < E; i++) {
        if (lines[i].valid && lines[i].tag == tag) {
            lines[i].stamp = stamp;
            verbose(" hit");
            hitCount++;
            return 1;
        }
    }
    verbose(" miss");
    missCount++;
    return 0;
}

void cache_eviction(uint64_t newTag, CacheLine *line) {
    verbose(" eviction");
    line->tag = newTag;
    evictionCount++;
}

void cache_load(uint64_t tag, uint64_t set) {
    stamp++;
    CacheLine *lines = cache[set];
    CacheLine *line, *minStampLine = lines, *endOfSet = lines + E;
    for (line = lines; line < endOfSet; line++) {
        if (!line->valid) {
            line->valid = 1;
            line->tag = tag;
            line->stamp = stamp;
            return;
        }
        else {
            if (line->stamp < minStampLine->stamp) minStampLine = line;
        }
    }
    cache_eviction(tag, minStampLine);
    minStampLine->stamp = stamp;
}

int use_data(uint64_t tag, uint64_t set) {
    if (cache_hit(tag, set)) {
        return 0;
    } else {
        cache_load(tag, set);
        return 1;
    }
}

void simulate_cache() {
    uint64_t mask = S - 1;
    stamp = 0;

    char op;
    uint64_t addr;
    uint32_t size;
    while (~fscanf(traceFile, "%c %lx, %x", &op, &addr, &size)) {
        uint64_t set = (addr >> b) & mask;
        uint64_t tag = addr >> (b+s);

        if (op == 'L') {
            use_data(tag, set);
        } else if (op == 'S') {
            use_data(tag, set);
        } else if (op == 'M') {
            use_data(tag, set);
            use_data(tag, set);
        }
    }
}

int main(int argc, char **argv)
{
    phase_argv(argc, argv);
    init_cache();

    simulate_cache();
    free_cache();

    printSummary(hitCount, missCount, evictionCount);
    return 0;
}
