typedef struct {
    char *path;
    char *addr;
    size_t size;
} File_mapped;

File_mapped file_mmapR(char *path);
void file_free(File_mapped file);
