#include "file_list.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "utils.h"

#define INITIAL_CAP 128
#define PATH_MAX_LEN 4096

static char **paths = NULL;
static size_t count = 0, capacity = 0;

void init_file_list(void) {
    capacity = INITIAL_CAP;
    paths = calloc(capacity, sizeof(char*));
    count = 0;
}

void cleanup_file_list(void) {
    for (size_t i = 0; i < count; ++i) free(paths[i]);
    free(paths);
    paths = NULL; capacity = count = 0;
}

static void add_path(const char *path) {
    if (count == capacity) {
        capacity *= 2;
        paths = realloc(paths, capacity * sizeof(char*));
    }
    paths[count++] = strdup(path);
}

void walk_dir(const char *dirpath) {
    DIR *d = opendir(dirpath);
    if (!d) { perror_msg("opendir", dirpath); return; }
    struct dirent *ent;
    char buf[PATH_MAX_LEN];
    while ((ent = readdir(d))) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..") || !strcmp(ent->d_name, ".git")) continue;
        snprintf(buf, sizeof(buf), "%s/%s", dirpath, ent->d_name);
        struct stat st;
        if (lstat(buf, &st) < 0) continue;
        if (S_ISDIR(st.st_mode)) walk_dir(buf);
        else if (S_ISREG(st.st_mode))  {
            if (ent->d_type == DT_REG) {  
            const char *dot = strrchr(ent->d_name, '.');
            if (dot && strcmp(dot, ".txt") == 0) {
                printf("Found text file: %s\n", buf);
                add_path(buf);
                continue;
            }
        }
            printf("Non Text File: %s\n", buf);
        }
    }
    closedir(d);
}

size_t file_list_count(void) {
    return count;
}

const char* file_list_get(size_t index) {
    return paths[index];
}