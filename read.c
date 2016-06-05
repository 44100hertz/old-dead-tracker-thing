#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "file.h"
#include "wave.h"

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

/* Read a pcmlib from a file */
void read_pcmlib(char *addr, Wave **wave)
{
        /* Magic number */
        if(strncmp(&addr[0], "SamPLE", 6)) {
                fprintf(stderr, "Not a pcmlib file!");
                return;
        }
        char *head = addr;
        char *end = addr+sizeof(addr);
        while(head<end) {
                switch(head) {
                }
                ++head;
        }
}


