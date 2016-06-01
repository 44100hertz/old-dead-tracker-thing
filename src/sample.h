#include <stdint.h>
#include <stdio.h>

typedef struct {
        char *name;
        file_type file;
} Sample;

Sample *sample_fromRaw(char *filename, char *name);
void sample_free(Sample *sample);
