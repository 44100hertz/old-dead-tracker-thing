#include <stdint.h>

/* Simply return the pointer passed to it, and move it forward amount size
 * Serves as a way to replace head+=X on every other line */
char *getdata(char **head, uint16_t size)
{
    char *data = *head;
    *head+=size;
    return data;
}
/* Convenience functions */
uint32_t get32(char **head) { return *(uint16_t*)getdata(head, 2); }
uint16_t get16(char **head) { return *(uint16_t*)getdata(head, 2); }
uint8_t   get8(char **head)  { return *(uint8_t*)getdata(head, 1); }
