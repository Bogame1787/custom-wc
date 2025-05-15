#include <unistd.h>    // for read(), write(), close()
#include <fcntl.h>     // for open() and file flags like O_RDONLY
#include <sys/types.h> // for types like ssize_t
#include <sys/stat.h>  // for struct stat, used with open()
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH_SIZE 4096

void count_words(char *filename);

void walk_dir(char *dirname) {
    DIR *dir = opendir(dirname);

    if(!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    while(entry = readdir(dir)) {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".git") == 0) continue;
        char path[MAX_PATH_SIZE];

        strcpy(path, dirname);
        strcat(path, "/");
        strcat(path, entry->d_name);

        struct stat st;
        if (stat(path, &st) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            walk_dir(path);
        } else if (S_ISREG(st.st_mode)) {
            if (entry->d_type == DT_REG) {  
            const char *dot = strrchr(entry->d_name, '.');
            if (dot && strcmp(dot, ".txt") == 0) {
                printf("Found text file: %s\n", path);
                count_words(path);
                continue;
            }
        }
            printf("File: %s\n", path);
        }
    }

    closedir(dir);
}

void count_words(char *filename) {
    int fd = open(filename, O_RDONLY);
    char buf[512];
    int n, num_bytes = 0, num_words = 0, num_lines = 0, in_word = 0;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        num_bytes += n;

        for (int i = 0; i < n; i++) {
            char ch = buf[i];

            if (ch == '\n') num_lines++;

            if (ch == ' ' || ch == '\n' || ch == '\t') {
                in_word = 0;
            } else if (!in_word) {
                in_word = 1;
                num_words++;
            }
        }
    }
    

    printf("%d %d %d", num_bytes, num_lines+1, num_words);

    return;
}

void main() {
    // char buf[512];
    // int names_fd = open("./names.txt", O_RDONLY);

    // read(names_fd, buf, sizeof(buf));

    // printf("%s", buf);
    
    walk_dir(".");

    return;
}