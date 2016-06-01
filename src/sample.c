/* to-come-later code for sample editor */

#include "file.h"
#include "sample.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Sample *sample_fromRaw(char *filename, char *name)
{
        Sample *sample = malloc(sizeof(Sample));

	sample->name = strdup(name);
	sample->file = file_mmap(filename);

	return sample;
}

void sample_free(Sample *sample)
{
	free(sample->name);
        
	free(sample);
}
