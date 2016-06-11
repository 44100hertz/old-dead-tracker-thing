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

/* Simply return the pointer passed to it, and move it forward amount size
 * Serves as a way to replace head+=X on every other line */
static inline
char *getdata(char **head, uint32_t size)
{
    char *data = *head;
    *head+=size;
    return data;
}
/* Convenience functions */
static inline uint32_t get32(char **head) { return *(uint32_t*)getdata(head, 4); }
static inline uint16_t get16(char **head) { return *(uint16_t*)getdata(head, 2); }
static inline uint8_t   get8(char **head)  { return *(uint8_t*)getdata(head, 1); }

/* Parse the initial song header */
static
void parse_song(Song *song, char **head)
{
    char numParams = get8(head);
    for(uint8_t i=0; i<numParams; i++) {
        char magic = get8(head);
        uint32_t size = get32(head);
        switch(magic) {
        case ID_NUMWAVES: song->numWaves = get16(head); break;
        }
    }
}

/* Parse a wave header */
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
            wave->data = getdata(head, size);
            break;
        case ID_TEXT:
            wave->textSize = size;
            wave->text = getdata(head, size);
            break;
        case ID_SRATE: wave->srate = get16(head); break;
        }
    }
}

/* Call parsing functions for the song header and each wave */
static
void parse(Song *song, char **head)
{
    if(!strcmp(getdata(head, 6), "SamPLE")) {
        printf("Not a pcmlib file!");
        return;
    }
    parse_song(song, head);
    song->wave = malloc(song->numWaves * sizeof(Wave));
    for(uint16_t i=0; i<song->numWaves; i++) {
        parse_wave(&song->wave[i], head);
    }
}

/* Read PCMlib.
 * Parses a standard .pcmlib file, putting data into song accordingly.
 * TODO: error/segfault handling using file.size */
void read_pcmlib(Song *song, File_mapped file)
{
    char *head = file.addr;
    parse(song, &head);
}
