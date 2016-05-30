#include <stdio.h>
#include <stdint.h>
#include "sample.h"

int main(int argc, char **argv)
{
	static uint16_t sampleSize = 26356;
		
	FILE *in, *out;

	in = stdin;
	out = stdout;

	sample_type *sample = sample_fromRaw(in, sampleSize, "test");
	sample_free(sample);

	return 0;
}
