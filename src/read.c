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
#include "get.h"

/* Parse the initial song header */
static
void parse_song(Song *song, char **head)
{
    char numParams = get8(head);
    for(uint8_t i=0; i<numParams; i++) {
        char magic = get8(head);
        uint16_t size = get16(head);
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
        uint16_t size = get16(head);
        switch(magic) {
        case ID_DATA:
            wave->data_size = size;
            wave->data = getdata(head, size);
            break;
        case ID_TEXT:
            wave->text_size = size;
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
    if(memcmp(getdata(head, 6), "SampLE", 6)) {
        printf("Not a pcmlib file!\n");
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
