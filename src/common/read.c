#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "file.h"
#include "song.h"
#include "read.h"

void parse(Song *song, char *head, uint32_t bsize)
{
    char *end = head + bsize;
    while(head<end) {
        char magic = head[0];
        uint32_t size = *(uint32_t*)&head[1];
        head+=5;
        switch(magic) {
            head+=size;
        }
    }
}

void read_pcmlib(char *filename, Song *song)
{
    song->pcmlib = file_mmapR(filename);
    if(strcmp(song->pcmlib.addr, "SamPLE")) {
        fprintf(stderr, "Not a pcmlib file!");
        return;
    }
    char *head = song->pcmlib.addr;
    uint32_t size = song->pcmlib.size;
    parse(song, head, size);
}


