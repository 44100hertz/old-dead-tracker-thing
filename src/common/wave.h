typedef struct {
        int8_t *data;
        char *name;
        int16_t srate;
} Wave;

void readpcmlib(char *addr, Wave *wave[]);
