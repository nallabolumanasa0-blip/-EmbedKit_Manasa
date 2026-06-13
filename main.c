
#include <stdio.h>
#include "ringbuf.h"

int main()
{
    queue_t q;
    uint8_t data;
    int ret;
    int i;

    init(&q);

    // Write 0x41 to 0x48 
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

    // Attempt one more write 
    ret = write(&q, 0x99);

    if(ret == FAILURE)
        printf("[WRITE] 0x99 -> FAIL (buffer full)\n");

    // Read 3 bytes 
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

    // Read all remaining bytes 
    while(!isempty(&q))
    {
        ret = read(&q, &data);

        if(ret == SUCCESS)
        {
            printf("[READ] -> 0x%02X (count=%d)\n",
                   data, get_count(&q));
        }
    }

    // Attempt one more read 
    ret = read(&q, &data);

    if(ret == FAILURE)
        printf("[READ] (empty) -> FAIL (buffer empty)\n");

    return 0;
}
