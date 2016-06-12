typedef struct {
    char *data;
    char *text;
    uint16_t data_size;
    uint16_t text_size;
    uint16_t srate;
} Wave;

typedef struct {
    uint16_t numWaves;
    Wave *wave;
} Song;

enum {
    ID_NUMWAVES = 'N',
    ID_DATA = 'd',
    ID_TEXT = 't',
    ID_SRATE = 's',
};
