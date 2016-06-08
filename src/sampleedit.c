#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "common/file.h"
#include "common/song.h"
#include "common/read.h"

void debug_file(char *filename)
{
    printf("Attempting to map file: %s\n", filename);
    File_mapped file = file_mmapR(filename);
    if(file.size!=-1) {
        printf("Mapped file!\nname:\t%s\naddr:\t%p\nsize:\t%d\n",
               file.filename, file.addr, file.size);
    }
}

int main(int argc, char **argv)
{
    Song *song = malloc(sizeof(Song));
    for(int i=1; i<argc; ++i) {
        if(!strcmp(argv[i],"read") && argc>=i) {
            song->pcmlib = file_mmapR(argv[++i]);
            read_pcmlib(song);
        } else if(!strcmp(argv[i],"debugfile") && argc>=i) {
            debug_file(argv[++i]);
        }
    }
    free(song->wave);
    free(song);
    return 0;
}
