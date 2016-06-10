typedef struct {
    uint32_t dataSize;
    uint32_t textSize;
    char *data;
    char *text;
    uint16_t srate;
} Wave;

typedef struct {
    uint16_t numWaves;
    Wave *wave;
} Song;

/* comment */
enum {
    ID_NUMWAVES = 0x00,
    ID_DATA,
    ID_TEXT,
    ID_SRATE,
    BLOCK = 0x80,
};
