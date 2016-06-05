#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "file.h"
#include "song.h"
#include "read.h"

static inline
uint32_t read32(char *addr)
{
        return(addr[0] << 24 | addr[1] << 16 | addr[2] << 8 | addr[3]);
}

static inline
uint16_t read16(char *addr)
{
        return(addr[0] << 8 | addr[0]);
}

void read_pcmlib(char *filename, Song *song)
{
        song->pcmlib = file_mmapR(filename);
        if(strncmp(song->pcmlib.addr, "SamPLE", 6)) {
                fprintf(stderr, "Not a pcmlib file!");
                return;
        }
        char *head = song->pcmlib.addr;
        char *end = song->pcmlib.addr + song->pcmlib.size;
        while(head<end) {
                switch(*head) {
                        /* read in MagicSizeData */
                }
                ++head;
        }
}


