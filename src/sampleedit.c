#include <stdio.h>
#include <stdint.h>
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
    Song song;
    for(int i=1; i<argc; ++i) {
        if(!strcmp(argv[i],"read"))
            read_pcmlib(argv[++i], &song);
        if(!strcmp(argv[i],"debugfile"))
            debug_file(argv[++i]);
    }
    return 0;
}
