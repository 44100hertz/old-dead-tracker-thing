#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "song.h"
#include "write.h"

static
void writeEntry(FILE *out, char id, uint32_t size, void *data)
{
    putc(id, out);
    fwrite(&size, 4, 1, out);
    fwrite(data, 1, size, out);
}

void write_pcmlib(FILE *out, Song *song)
{
    fprintf(out, "SampLE");
    /* Number of entries in header */
    putc(0x01, out);
    /* Entries in header */
    writeEntry(out, ID_NUMWAVES, 2, &song->numWaves);
    for(uint16_t i=0; i<song->numWaves; i++) {
        Wave wave = song->wave[i];
        /* Number of entries in wave data */
        uint16_t count = 0;
        if(wave.dataSize>0) count++;
        if(wave.textSize>0) count++;
        if(wave.srate>0) count++;
        putc(count, out);
        /* Entries in wave data */
        if(wave.srate>0)
            writeEntry(out, ID_SRATE, 2, &wave.srate);
        if(wave.textSize>0)
            writeEntry(out, ID_TEXT, wave.textSize, wave.text);
        if(wave.dataSize>0)
            writeEntry(out, ID_DATA, wave.dataSize, wave.data);
    }
}
