typedef struct {
        int8_t *data;
        uint16_t textSize;
        char *text;
        int16_t srate;
} Wave;

typedef struct {
        File_mapped pcmlib;
        uint16_t textSize;
        char *text;
        uint16_t numWaves;
        Wave *waves;
} Song;
