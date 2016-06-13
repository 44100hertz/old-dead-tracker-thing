#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "file.h"

File_mapped file_mmapR(char *path)
{
    /* "filedescriptor" fd is arbitrary unix number for file access */
    int fd = open(path, O_RDONLY);
    /* struct sb contains various file info */
    struct stat sb;
    fstat(fd, &sb);
    /* NULL means map it to any address. 0 is file offset */
    char *addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    /* closing the file probably still keeps the mmap alive */
    close(fd);

    if(addr == MAP_FAILED) {
        fprintf(stderr, "Can't mmap file (no RAM or bad file)\n");
        return (File_mapped){NULL, NULL, -1};
    }

    File_mapped file;
    file.path = path;
    file.addr = addr;
    /* casts off_t to size_t. Probably okay? */
    file.size = sb.st_size;

    return file;
}

void file_free(File_mapped file) {
    if(file.addr!=NULL)  munmap(file.addr, file.size);
}
