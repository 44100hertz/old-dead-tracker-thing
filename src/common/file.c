#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "file.h"

/* TODO: add filename handling */
/* TODO: rename "file_type" to "File" */
file_type file_mmap(char *filename)
{
        /* "filedescriptor" fd is arbitrary unix number for file access */
        int fd = open(filename, O_RDONLY);
        /* struct sb contains various file info */
        struct stat sb;
        fstat(fd, &sb);
        /* NULL means map it to any address. 0 is file offset */
        char *addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        /* closing the file probably still keeps the mmap alive */
        close(fd);

        if(addr == MAP_FAILED) {
                fprintf(stderr, "Can't mmap file (no RAM or bad file)");
                return (file_type){NULL, -1};
        }

        file_type file;
        file.addr = addr;
        /* casts off_t to size_t. Probably okay? */
        file.size = sb.st_size;

        return file;
}

void file_free(file_type *file) {
        munmap(file->addr, file->size);
        free(file);
}
