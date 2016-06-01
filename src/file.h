#include <stdlib.h> /* for size_t */

typedef struct {
        char *addr;
        size_t size;
} file_type;

file_type file_mmap(char *filename);
void file_free(file_type *file);
