#include "workers.h"
#include "file_list.h"
#include "wc_count.h"
#include "utils.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

static size_t next_file = 0;
static wc_count_t total = {0,0,0};

static sem_t next_sem;
static sem_t total_sem;

static void* worker(void* _) {
    (void)_;
    while (1) {
        sem_wait(&next_sem);
        size_t idx = next_file++;
        sem_post(&next_sem);
        if (idx >= file_list_count()) break;

        const char* path = file_list_get(idx);
        wc_count_t c = count_file(path);

        sem_wait(&total_sem);
        printf("%8lu %8lu %8lu  %s\n",
               c.lines, c.words, c.bytes, path);
        total.lines += c.lines;
        total.words += c.words;
        total.bytes += c.bytes;
        sem_post(&total_sem);
    }
    return NULL;
}

void dispatch_workers(int thread_count) {
    sem_init(&next_sem,  0, 1);
    sem_init(&total_sem, 0, 1);

    pthread_t *tids = malloc(thread_count * sizeof(pthread_t));
    for (int i = 0; i < thread_count; ++i)
        pthread_create(&tids[i], NULL, worker, NULL);
    for (int i = 0; i < thread_count; ++i)
        pthread_join(tids[i], NULL);

    sem_destroy(&next_sem);
    sem_destroy(&total_sem);
    free(tids);
}

void print_total(void) {
    printf("%8lu %8lu %8lu  total\n",
           total.lines, total.words, total.bytes);
}