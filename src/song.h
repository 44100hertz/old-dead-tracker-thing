typedef struct {
    uint16_t dataSize;
    uint16_t textSize;
    char *data;
    char *text;
    uint16_t srate;
} Wave;

typedef struct {
    uint16_t numWaves;
    Wave *wave;
} Song;

/* ONLY append to this list, or incompatabilies will happen */
enum {
    ID_NUMWAVES = 0x00,
    ID_DATA,
    ID_TEXT,
    ID_SRATE,
    BLOCK = 0x80,
};
