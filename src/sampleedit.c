#include <stdio.h>
#include <stdint.h>
#include "common/file.h"

int debug()
{
        File_mapped file = file_mmapR("test.pcm");
        if(file.size!=-1) {
                printf("Mapped file!\nname:\t%s\naddr:\t%p\nsize:\t%d\n",
                       file.filename, file.addr, file.size);
        }
        file_free(file);
        return 0;
}

int main(int argc, char **argv)
{
        for(int arg=1; arg<argc; ++arg) {
                
        }
        return debug();
}
