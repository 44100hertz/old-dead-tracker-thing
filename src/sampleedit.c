#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "common/file.h"
#include "common/song.h"
#include "common/read.h"
#include "common/write.h"

File_mapped debug_mmap(char *filename)
{
    printf("Attempting to map file: %s\n", filename);
    File_mapped file = file_mmapR(filename);
    if(file.size!=-1) {
        printf("Mapped file!\nname:\t%s\naddr:\t%p\nsize:\t%d\n",
               file.filename, file.addr, file.size);
    }
    return file;
}

void debug_write(char *filename)
{
    FILE *out = fopen(filename, "w");
    Wave wave[1] = {8, 8, "DATADATA", "TEXTTEXT", 44100};
    File_mapped dummyFile = {NULL, NULL};
    Song *song = &(Song){dummyFile, 1, wave};
    write_pcmlib(out, song);
    fclose(out);

    printf("Wrote file: %s\n", filename);
}

int main(int argc, char **argv)
{
    Song *song = malloc(sizeof(Song));;
    for(int i=1; i+1<argc; ++i) {
        if(!strcmp(argv[i],"read")) {
            song->pcmlib = file_mmapR(argv[++i]);
            read_pcmlib(song);
        } else if(!strcmp(argv[i],"write")) {
            FILE *out = fopen(argv[++i], "w");
            write_pcmlib(out, song);
        } else if(!strcmp(argv[i],"debugwrite")) {
            debug_write(argv[++i]);
        } else if(!strcmp(argv[i],"debugmmap") && argc>=i) {
            debug_mmap(argv[++i]);
        }
    }
    free(song->wave);
    file_free(song->pcmlib);
    free(song);
    return 0;
}
