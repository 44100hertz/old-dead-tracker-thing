#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "song.h"
#include "write.h"

static inline
void put16(FILE *out, uint16_t data)
{
    fprintf(out, "%c%c", data<<8, data);
}
static inline
void put32(FILE *out, uint32_t data)
{
    fprintf(out, "%c%c%c%c", data<<24, data<<16, data<<8, data);
}

static
void writeEntry(FILE *out, uint16_t id, uint32_t size, void *addr)
{
    put16(out, id);
    put32(out, size);
    fwrite(addr, 1, size, out);
}

void write_pcmlib(FILE *out, Song *song)
{
    fprintf(out, "SampLE");
    put16(out, 1); /* number of entries */
    writeEntry(out, ID_NUMWAVES, 2, &song->numWaves);
    for(uint16_t i=0; i<song->numWaves; i++) {
        Wave wave = song->wave[i];
        uint16_t count = 0;
        if(wave.dataSize>0) count++;
        if(wave.textSize>0) count++;
        if(wave.srate>0) count++;
        put16(out, count);
        if(wave.srate>0)
            writeEntry(out, ID_SRATE, 2, &wave.srate);
        if(wave.textSize>0)
            writeEntry(out, ID_TEXT, wave.textSize, wave.text);
        if(wave.dataSize>0)
            writeEntry(out, ID_DATA, wave.dataSize, wave.data);
    }
}
