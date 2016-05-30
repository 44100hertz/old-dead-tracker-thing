#include <stdint.h>
#include <stdio.h>

typedef struct {
	char *name;
	int8_t *data;
} sample_type;

sample_type *sample_fromRaw(FILE *in, uint16_t readSize, char *name);
void sample_free(sample_type *sample);
