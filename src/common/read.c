/* Read in pcmlib and/or song data.
 * "MSD" format
 * M SSSS DDDDDDD...
 * M = magic number / id
 * S = size of data
 * d = data itself
 *
 * General format:
 * X MSD MSD MSD
 * X = number of MSD entries
 *
 * Pcmlib format:
 * Header, then waves. Both use general format.
 * Number of waves defined in header.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "song.h"
#include "read.h"

static inline uint8_t get8(char **addr)
{
    uint8_t value = **addr;
    *addr+=1;
    return value;
}
static inline uint16_t get16(char **addr)
{
    uint16_t value = **(uint16_t**)addr;
    *addr+=2;
    return value;
}
static inline uint32_t get32(char **addr)
{
    uint32_t value = **(uint32_t**)addr;
    *addr+=4;
    return value;
}

static
void parse_song(Song *song, char **head)
{
    char numParams = get8(head);
    for(uint8_t i=0; i<numParams; i++) {
        char magic = get8(head);
        uint32_t size = get32(head);
        switch(magic) {
        case ID_NUMWAVES:
            song->numWaves = get16(head);
        }
    }
}

static
void parse_wave(Wave *wave, char **head)
{
    char numParams = get8(head);
    for(uint8_t i=0; i<numParams; i++) {
        char magic = get8(head);
        uint32_t size = get32(head);
        switch(magic) {
        case ID_DATA:
            wave->dataSize = size;
            wave->data = *head;
            *head += size;
            break;
        case ID_TEXT:
            wave->textSize = size;
            wave->text = *head;
            *head += size;
            break;
        case ID_SRATE:
            wave->srate = get16(head);
            break;
        }
    }
}

static
void parse(Song *song, char **head)
{
    parse_song(song, head);
    for(uint16_t i=0; i<song->numWaves; i++) {
        parse_wave(&song->wave[i], head);
    }
}

void read_pcmlib(Song *song, File_mapped file)
{
    char *head = file.addr;
    if(!strcmp(head+=6, "SamPLE")) {
        fprintf(stderr, "Not a pcmlib file!");
        return;
    }
    song->numWaves = get16(&head);
    song->wave = malloc(song->numWaves * sizeof(Wave));
    parse(song, &head);
}
