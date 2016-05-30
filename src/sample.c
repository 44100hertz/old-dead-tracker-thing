#include "sample.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

sample_type *sample_fromRaw(FILE *in, uint16_t readSize, char *name)
{
	sample_type *sample = malloc(sizeof(sample_type));
	assert(sample!=NULL);
	
	sample->name = strdup(name);
	sample->data = malloc(readSize);

	for(int i=0; i<readSize; ++i) {
		char c = getc(in);
		assert(c!=EOF);
		sample->data[i] = c;
	}
	
	return sample;
}

void sample_free(sample_type *sample)
{
	assert(sample!=NULL);
	
	free(sample->name);
	free(sample->data);
	free(sample);
}
