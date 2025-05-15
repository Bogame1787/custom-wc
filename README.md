# custom-wc

> A custom, multithreaded implementation of the classic UNIX `wc` utility, using semaphores for synchronization.

## Features

- **Parallel file counting**: Spawn multiple worker threads to count lines, words, and bytes concurrently.  
- **Semaphore-based synchronization**: Protects work dispatch and global totals with lightweight POSIX semaphores.  
- **Modular codebase**:  
  - `src/file_list.{c,h}` – Recursively collect regular files in a directory  
  - `src/wc_count.{c,h}` – Fast per-file line/word/byte counting  
  - `src/workers.{c,h}`  – Thread pool, work scheduling, and aggregation  
  - `src/utils.{c,h}`    – Common helpers and error wrappers  
  - `src/main.c`         – CLI parsing, initialization, orchestration  

## Build

```bash
# From the repository root
make
