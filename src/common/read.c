/* Read in pcmlib and/or song data.
 * Data is stored in a tree, laid out in the file like:
 * MMNNSSSSdddd...
 * M = magic number / id
 * N = number of children
 * S = size of data
 * d = data itself, plus child nodes and their data
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "song.h"
#include "read.h"

static inline uint16_t get16(char *addr) { return *(uint16_t*)(addr); }
static inline uint32_t get32(char *addr) { return *(uint32_t*)(addr); }

static
uint32_t parse(Song *song, char *head, int16_t index)
{
    uint16_t magic = get16(head+=2);
    uint32_t size = get32(head+=4);
    if(index==-1) {
        for(uint16_t i=0; i<song->numWaves; i++) {
            head += parse(song, head, i);
        }
    }
    switch(magic) {
    case ID_DATA:
        song->wave[index].dataSize = size;
        song->wave[index].data = head;
        break;
    case ID_TEXT:
        song->wave[index].textSize = size;
        song->wave[index].text = head;
        break;
    case ID_SRATE:
        song->wave[index].srate = get16(head);
    }
    head += size;
    return 8+size; /* 8 is magic+numChildren+size */
}

void read_pcmlib(Song *song)
{
    char *head = song->pcmlib.addr;
    if(!strcmp(head+=6, "SamPLE")) {
        fprintf(stderr, "Not a pcmlib file!");
        return;
    }
    song->numWaves = get16(head+=2);
    song->wave = malloc(song->numWaves * sizeof(Wave));
    parse(song, head, -1);
    /* TODO: free this when actually needed */
    free(song->wave);
}
