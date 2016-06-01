#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "common/file.h"

int debug()
{
        File_mapped file = file_mmapR("test.pcm");
        file_free(file);
}

int main(int argc, char **argv)
{
        return debug();
}
