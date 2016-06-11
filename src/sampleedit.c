#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "common/file.h"
#include "common/song.h"
#include "common/read.h"
#include "common/write.h"

static
File_mapped debug_mmap(char *filename)
{
    printf("Attempting to map file: %s\n", filename);
    File_mapped file = file_mmapR(filename);
    if(file.size!=-1) {
        printf("Mapped file!\nname:\t%s\naddr:\t%p\nsize:\t%zd\n",
               file.filename, file.addr, file.size);
    }
    return file;
}

static
void debug_write(char *filename)
{
    FILE *out = fopen(filename, "w");
    Wave wave = {8, 8, "DATADATA", "TEXTTEXT", 44100};
    Song *song = &(Song){1, &wave};
    write_pcmlib(out, song);
    fclose(out);

    printf("Wrote file: %s\n", filename);
}

static
void songinfo(Song *song)
{
    printf("----- Song information -----\n");
    printf("> Number of waves: %d\n", song->numWaves);
    printf("----- Wave information -----\n");
    for(uint8_t i=0; i<song->numWaves; i++) {
        Wave wave = song->wave[i];
        printf("> Wave %d: %.*s\n", i, wave.textSize, wave.text);
        printf("  > Data size: %d\n", wave.dataSize);
        printf("  > Sample rate: %d\n", wave.srate);
    }
}

int main(int argc, char **argv)
{
    Song *song = malloc(sizeof(Song));
    File_mapped pcmlib;
    for(int i=1; i+1<argc; ++i) {
        if(!strcmp(argv[i],"read")) {
            printf("Opening file for reading: %s\n", argv[i+1]);
            pcmlib = file_mmapR(argv[++i]);
            read_pcmlib(song, pcmlib);
        } else if(!strcmp(argv[i],"write")) {
            printf("Opening file for writing: %s\n", argv[i+1]);
            FILE *out = fopen(argv[++i], "w");
            write_pcmlib(out, song);
        } else if(!strcmp(argv[i],"info")) {
            songinfo(song);
        } else if(!strcmp(argv[i],"debugwrite")) {
            debug_write(argv[++i]);
        } else if(!strcmp(argv[i],"debugmmap") && argc>=i) {
            debug_mmap(argv[++i]);
        }
    }
    file_free(pcmlib);
    free(song->wave);
    free(song);
    return 0;
}
