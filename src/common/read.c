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

/* Read in size amount of data.
 * Moves the head forward accordingly. */
static
char *getdata(char **head, uint8_t size)
{
    char *data = *head;
    *head+=size;
    return data;
}

/* Read in the Size and Data of MSD entry
 * Move the head to the next entry */
static
void readEntry(char **head, uint32_t *size, char *data)
{
    *size = *(uint32_t*)getdata(head, 4);
    *data = **head;
    *head += *size;
}

/* Parse the initial song header */
static
void parse_song(Song *song, char **head)
{
    char numParams = *getdata(head, 1);
    for(uint8_t i=0; i<numParams; i++) {
        char magic = *getdata(head, 1);
        switch(magic) {
        case ID_NUMWAVES: readEntry(head, NULL, (char*)&song->numWaves); break;
        }
    }
}

/* Parse a wave header */
static
void parse_wave(Wave *wave, char **head)
{
    char numParams = *getdata(head, 1);
    for(uint8_t i=0; i<numParams; i++) {
        char magic = *getdata(head, 1);
        switch(magic) {
        case ID_DATA: readEntry(head, &wave->dataSize, wave->data); break;
        case ID_TEXT: readEntry(head, &wave->textSize, wave->text); break;
        case ID_SRATE: readEntry(head, NULL, (char*)&wave->srate); break;
        }
    }
}

/* Whip the specialized parsing functions into shape */
static
void parse(Song *song, char **head)
{
    if(!strcmp(getdata(head, 6), "SamPLE")) {
        fprintf(stderr, "Not a pcmlib file!");
        return;
    }
    song->numWaves = *getdata(head, 2);
    song->wave = malloc(song->numWaves * sizeof(Wave));
    parse_song(song, head);
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
