#include <stdio.h>
#include "ringbuf.h"

void init(queue_t *q)
{
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

int isempty(queue_t *q)
{
    if(q->count == 0)
        return SUCCESS;
    else
        return FAILURE;
}

int isfull(queue_t *q)
{
    if(q->count == BUFFER_SIZE)
        return SUCCESS;
    else
        return FAILURE;
}

int write(queue_t *q, uint8_t data)
{
    if(isfull(q))
        return FAILURE;

    q->buffer[q->head] = data;

   
    q->head = (q->head + 1) & (BUFFER_SIZE - 1);

    q->count++;

    return SUCCESS;
}

int read(queue_t *q, uint8_t *data)
{
    if(isempty(q))
        return FAILURE;

    *data = q->buffer[q->tail];

    q->tail = (q->tail + 1) & (BUFFER_SIZE - 1);

    q->count--;

    return SUCCESS;
}

uint8_t get_count(queue_t *q)
{
    return q->count;
}
