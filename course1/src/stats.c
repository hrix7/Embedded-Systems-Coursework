#include "stats.h"
#include "platform.h"
#include <stdint.h>

void print_array(unsigned char *data, unsigned int length)
{
#if defined(VERBOSE) && defined(HOST)
    while (length--) PRINTF("%u ", (unsigned int)*data++);
    PRINTF("\n");
#else
    (void)data;
    (void)length;
#endif
}

void sort_array(unsigned char *data, unsigned int length)
{
    unsigned int i, j;
    if (!data) return;
    for (i = 0; i < length; ++i) {
        for (j = i + 1; j < length; ++j) {
            if (*(data + j) > *(data + i)) {
                unsigned char temp = *(data + i);
                *(data + i) = *(data + j);
                *(data + j) = temp;
            }
        }
    }
}
unsigned char find_median(unsigned char *data, unsigned int length)
{
    if (!data || !length) return 0;
    sort_array(data, length);
    if (length % 2) return *(data + length / 2);
    return (unsigned char)(((unsigned int)*(data + length/2 - 1)
                           + *(data + length/2)) / 2);
}
unsigned char find_mean(unsigned char *data, unsigned int length)
{
    uint64_t total = 0;
    unsigned int i;
    if (!data || !length) return 0;
    for (i = 0; i < length; ++i) total += *(data + i);
    return (unsigned char)(total / length);
}
unsigned char find_maximum(unsigned char *data, unsigned int length)
{
    unsigned char value;
    if (!data || !length) return 0;
    value = *data;
    while (length--) { if (*data > value) value = *data; ++data; }
    return value;
}
unsigned char find_minimum(unsigned char *data, unsigned int length)
{
    unsigned char value;
    if (!data || !length) return 0;
    value = *data;
    while (length--) { if (*data < value) value = *data; ++data; }
    return value;
}
void print_statistics(unsigned char *data, unsigned int length)
{
    PRINTF("Minimum: %u\n", (unsigned int)find_minimum(data, length));
    PRINTF("Maximum: %u\n", (unsigned int)find_maximum(data, length));
    PRINTF("Mean: %u\n", (unsigned int)find_mean(data, length));
    PRINTF("Median: %u\n", (unsigned int)find_median(data, length));
    (void)data;
    (void)length;
}
