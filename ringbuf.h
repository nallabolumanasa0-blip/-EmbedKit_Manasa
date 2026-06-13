#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdint.h>

#define BUFFER_SIZE 8
#define SUCCESS     1
#define FAILURE     0

typedef struct que
{
    uint8_t head;
    uint8_t tail;
    uint8_t count;
    uint8_t buffer[BUFFER_SIZE];

}queue_t;

void init(queue_t *q);
int isempty(queue_t *q);
int isfull(queue_t *q);
int write(queue_t *q, uint8_t data);
int read(queue_t *q, uint8_t *data);
uint8_t get_count(queue_t *q);

#endif
