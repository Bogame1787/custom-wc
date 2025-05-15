#ifndef FILE_LIST_H
#define FILE_LIST_H

#include <stddef.h>

void init_file_list(void);
void cleanup_file_list(void);
void walk_dir(const char *dirpath);
size_t file_list_count(void);
const char* file_list_get(size_t index);

#endif 
