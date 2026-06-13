
#include<stdio.h>
#include<stdint.h>

#define BUFFER_SIZE 8
#define SUCCESS     1
#define FAILURE     0

typedef struct que
{
    uint8_t head;
    uint8_t tail;
    uint8_t count;
    uint8_t buffer[BUFFER_SIZE];

} queue_t;

// Initialize buffer
void init(queue_t *q)
{
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

// Check empty
int isempty(queue_t *q)
{
    if(q->count == 0)
        return SUCCESS;
    else
        return FAILURE;
}

// Check full
int isfull(queue_t *q)
{
    if(q->count == BUFFER_SIZE)
        return SUCCESS;
    else
        return FAILURE;
}

// Write one byte
int write(queue_t *q, uint8_t data)
{
    if(isfull(q))
        return FAILURE;

    q->buffer[q->head] = data;

    
    q->head = (q->head + 1) & (BUFFER_SIZE - 1);

    q->count++;

    return SUCCESS;
}

// Read one byte
int read(queue_t *q, uint8_t *data)
{
    if(isempty(q))
        return FAILURE;

    *data = q->buffer[q->tail];

    q->tail = (q->tail + 1) & (BUFFER_SIZE - 1);

    q->count--;

    return SUCCESS;
}

// Get count
uint8_t get_count(queue_t *q)
{
    return q->count;
}

int main()
{
    queue_t q;
    uint8_t data;
    int ret;
    int i;

    init(&q);

    //Step 1 : Write 0x41 to 0x48 
    for(i = 0; i < BUFFER_SIZE; i++)
    {
        data = 0x41 + i;

        ret = write(&q, data);

        if(ret == SUCCESS)
        {
            printf("[WRITE] 0x%02X -> OK (count=%d)",
                   data, get_count(&q));

            if(isfull(&q))
                printf(" FULL");

            printf("\n");
        }
    }

    // Write one more byte 
    ret = write(&q, 0x99);

    if(ret == FAILURE)
        printf("[WRITE] 0x99 -> FAIL (buffer full)\n");

    // Step 3 : Read 3 bytes 
    for(i = 0; i < 3; i++)
    {
        ret = read(&q, &data);

        if(ret == SUCCESS)
        {
            printf("[READ] -> 0x%02X (count=%d)\n",
                   data, get_count(&q));
        }
    }

    // Write 0x49, 0x4A, 0x4B 
    for(data = 0x49; data <= 0x4B; data++)
    {
        ret = write(&q, data);

        if(ret == SUCCESS)
        {
            printf("[WRITE] 0x%02X -> OK (count=%d)\n",
                   data, get_count(&q));
        }
    }

    //  Read all remaining bytes 
    while(!isempty(&q))
    {
        ret = read(&q, &data);

        if(ret == SUCCESS)
        {
            printf("[READ] -> 0x%02X (count=%d)\n",
                   data, get_count(&q));
        }
    }

    //  Read from empty buffer 
    ret = read(&q, &data);

    if(ret == FAILURE)
        printf("[READ] (empty) -> FAIL (buffer empty)\n");

    return 0;
}
