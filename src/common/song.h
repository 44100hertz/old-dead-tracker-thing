typedef struct {
        int8_t *data;
        char *name;
        int16_t srate;
} Wave;

typedef struct {
        File_mapped pcmlib;
        uint16_t numWaves;
        Wave *waves;
} Song;
