typedef struct {
    uint32_t dataSize;
    uint32_t textSize;
    char *data;
    char *text;
    uint16_t srate;
} Wave;

typedef struct {
    File_mapped pcmlib;
    uint16_t numWaves;
    Wave *wave;
} Song;

enum {
    ID_NUMWAVES,
    ID_DATA,
    ID_TEXT,
    ID_SRATE,
};
