typedef struct {
    char *filename;
    char *addr;
    size_t size;
} File_mapped;

File_mapped file_mmapR(char *filename);
void file_free(File_mapped file);
