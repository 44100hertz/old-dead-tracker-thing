#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "file.h"
#include "get.h"
#include "song.h"

#define MAX(x, y) (x>y)?x:y

static
uint32_t get32BE(char **head)
{
    uint32_t BEdata = *(uint32_t*)getdata(head, 4);
    uint32_t LEdata =
        (BEdata << 24 & 0xff000000) |
        (BEdata << 8  & 0x00ff0000) |
        (BEdata >> 8  & 0x0000ff00) |
        (BEdata >> 24 & 0x000000ff);
    return LEdata;
}

void import_RAW(Wave *wave, File_mapped file)
{
    wave->data_size = MAX(0xffff, file.size);
    wave->data = file.addr;
}

void import_AU(Wave *wave, File_mapped file)
{
    char *head = file.addr;

    char *magic =          getdata(&head, 4);
    uint32_t dataOffset =  get32BE(&head);
    uint32_t dataSize =    get32BE(&head);
    head+=4;
    /*uint32_t encoding = get32BE(&head);*/
    wave->srate =          get32BE(&head);
    head+=4;
    /*uint32_t numChannels = get32BE(&head);*/

    if(memcmp(magic, ".snd", 4)) {
        fprintf(stderr, "Not a .au file\n");
        return;
    }
    if(dataOffset!=0xffffffff) wave->data = file.addr+dataOffset;
    else wave->data = head;
    wave->data_size = MAX(0xffff, dataSize);
}
