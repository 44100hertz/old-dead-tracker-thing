#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
#include "file.h"
#include "read.h"
#include "write.h"
#include "import.h"

static
void read(Song *song, File_mapped pcmlib, char *path)
{
    printf("Opening file for reading: %s\n", path);
    pcmlib = file_mmapR(path);
    read_pcmlib(song, pcmlib);
}
static
void write(Song *song, char *path)
{
    printf("Opening file for writing: %s\n", path);
    FILE *out = fopen(path, "w");
    write_pcmlib(out, song);
}

static
void import(Song *song, char *path)
{
    printf("Importing file: %s\n", path);

    uint16_t *numWaves = &song->numWaves;
    *numWaves += 1;
    song->wave = realloc(song->wave, song->numWaves * sizeof(Wave));
    Wave *wave = &song->wave[(*numWaves)-1];

    File_mapped file = file_mmapR(path);
    char *filename = strrchr(path, '/');
    wave->text_size = strlen(path);
    wave->text = filename;

    char *exten = strrchr(path, '.');

    if(!strcmp(exten,".au") || !strcmp(exten,".AU")) {
        import_AU(wave, file);
    } else {
        import_RAW(wave, file);
    }
}

static
void songinfo(Song *song)
{
    printf("----- Song information -----\n");
    printf("> Number of waves: %d\n", song->numWaves);
    printf("----- Wave information -----\n");
    for(uint8_t i=0; i<song->numWaves; i++) {
        Wave wave = song->wave[i];
        printf("> Wave %d: %.*s\n", i, wave.text_size, wave.text);
        printf("  > Data size: %d\n", wave.data_size);
        printf("  > Sample rate: %d\n", wave.srate);
    }
}
#ifdef DEBUG
static
File_mapped debug_mmap(char *path)
{
    printf("Attempting to map file: %s\n", path);
    File_mapped file = file_mmapR(path);
    if(file.size!=-1) {
        printf("Mapped file!\nname:\t%s\naddr:\t%p\nsize:\t%zd\n",
               file.path, file.addr, file.size);
    }
    return file;
}

static
void debug_write(char *path)
{
    FILE *out = fopen(path, "w");
    Wave wave = {"DATADATA", "TEXTTEXT", 8, 8, 44100};
    Song *song = &(Song){1, &wave};
    write_pcmlib(out, song);
    fclose(out);

    printf("Wrote file: %s\n", path);
}
#endif

int main(int argc, char **argv)
{
    Song *song = malloc(sizeof(Song));
    File_mapped pcmlib;
    for(int i=0; i<argc; ++i) {
#define IFARG(string, abbrev) if(!strcmp(argv[i],string)||!strcmp(argv[i],abbrev))
#define ARGNEXT (argv[i+1][0]!='-' && (i<=argc+1))
        IFARG("--status", "-s") {
            songinfo(song);
        } else IFARG("--write", "-w") {
            if(ARGNEXT) write(song, argv[++i]);
        } else IFARG("--read", "-r") {
            if(ARGNEXT) read(song, pcmlib, argv[++i]);
        } else IFARG("--import", "-i") {
           while(ARGNEXT) import(song, argv[++i]);
#ifdef DEBUG
        } else IFARG("--debugwrite", "-dw") {
            if(ARGNEXT) debug_write(argv[++i]);
        } else IFARG("--debugmmap", "-dm") {
            if(ARGNEXT) debug_mmap(argv[++i]);
#endif
        } else IFARG("--help", "-h") {
            printf("waveedit:\n"
                   "  A way to read, write, and edit .pcmlib files used by funtracker.\n"
                   "  Arguments are interpreted as direct commands.\n"
                   "  --status/-s: print all information about the current pcmlib\n"
                   "  --read/-r:   read in a .pcmlib file. Does not append to current pcmlib\n"
                   "  --import/-i: read in .au or headerless .pcm, append to current pcmlib\n"
                   "  --write/-w:  write the current pcmlib to a file\n"
                   "  --help/-h:   print this message\n"
#ifdef DEBUG
                   "  --debugwrite: write a blank pcmlib file to filename\n"
                   "  --debugmmap:  test memory mapping filename\n"
#endif
                );
        }
    }
    file_free(pcmlib);
    free(song->wave);
    free(song);
    return 0;
}
