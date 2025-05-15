#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "file_list.h"
#include "workers.h"
#include "utils.h"

int main(int argc, char **argv) {
    char *dir = NULL;
    int threads = 0;
    int c;

    while ((c = getopt(argc, argv, "d:p:")) != -1) {
        switch (c) {
        case 'd': dir     = optarg; break;
        case 'p': threads = atoi(optarg); break;
        default:  usage(argv[0]);
        }
    }
    if (!dir || threads <= 0) usage(argv[0]);

    init_file_list();
    walk_dir(dir);
    if (file_list_count() == 0) {
        fprintf(stderr, "No files found in %s\n", dir);
        return 1;
    }

    dispatch_workers(threads);
    print_total();
    cleanup_file_list();
    return 0;
}