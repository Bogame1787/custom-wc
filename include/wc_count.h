#ifndef WC_COUNT_H
#define WC_COUNT_H

#include <stdint.h>

typedef struct {
    uint64_t lines;
    uint64_t words;
    uint64_t bytes;
} wc_count_t;

wc_count_t count_file(const char *path);

#endif // WC_COUNT_H