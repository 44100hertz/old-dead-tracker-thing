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
char *parse_song(Song *song, char *head)
{
    uint16_t numParams = get16(head+=2);
    for(int16_t i=0; i<numParams; i++) {
        uint16_t magic = get16(head+=2);
        uint32_t size = get32(head+=4);
        switch(magic) {
        case ID_NUMWAVES:
            song->numWaves = get16(head);
        }
    }
    return head;
}

static
char *parse_wave(Wave *wave, char *head)
{
    uint16_t numParams = get16(head+=2);
    for(int16_t i=0; i<numParams; i++) {
        uint16_t magic = get16(head+=2);
        uint32_t size = get32(head+=4);
        switch(magic) {
        case ID_DATA:
            wave->dataSize = size;
            wave->data = head;
            break;
        case ID_TEXT:
            wave->textSize = size;
            wave->text = head;
            break;
        case ID_SRATE:
            wave->srate = get16(head);
            break;
        }
        head += size;
    }
    return head;
}

static
void parse(Song *song, char *head)
{
    head = parse_song(song, head);
    for(uint16_t i=0; i<song->numWaves; i++) {
        head = parse_wave(&song->wave[i], head);
    }
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
    parse(song, head);
}
