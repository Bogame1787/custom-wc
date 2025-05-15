#include "wc_count.h"
#include <stdio.h>
#include <errno.h>

wc_count_t count_file(const char *path) {
    FILE *f = fopen(path, "rb");
    wc_count_t c = {0,0,0};
    if (!f) { perror(path); return c; }

    int in_word = 0;
    char buf[8192];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        c.bytes += n;
        for (size_t i = 0; i < n; ++i) {
            char ch = buf[i];
            if (ch == '\n') c.lines++;
            if (ch==' '||ch=='\n'||ch=='\t'||ch=='\r')
                in_word = 0;
            else if (!in_word) {
                in_word = 1;
                c.words++;
            }
        }
    }
    fclose(f);
    return c;
}