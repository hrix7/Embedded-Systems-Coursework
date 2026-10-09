/* Integer/ASCII conversion using pointer arithmetic; no string library. */
#include "data.h"
#include "memory.h"
#include <stddef.h>
#include <limits.h>

uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base)
{
    uint8_t *start = ptr;
    uint8_t *first;
    uint32_t magnitude;
    if (!ptr) return 0;
    if (base < 2 || base > 16) { *ptr = 0; return 1; }
    /* Unsigned subtraction avoids signed overflow at INT32_MIN. */
    magnitude = data < 0 ? 0u - (uint32_t)data : (uint32_t)data;
    if (data < 0) *ptr++ = '-';
    first = ptr;
    do {
        uint32_t digit = magnitude % base;
        *ptr++ = (uint8_t)(digit < 10 ? '0' + digit : 'A' + digit - 10);
        magnitude /= base;
    } while (magnitude);
    my_reverse(first, (size_t)(ptr - first));
    *ptr++ = 0;
    return (uint8_t)(ptr - start);
}

int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base)
{
    uint32_t magnitude = 0;
    uint32_t limit = INT32_MAX;
    uint8_t negative = 0;
    if (!ptr || !digits || base < 2 || base > 16) return 0;
    if (*ptr == '-') {
        negative = 1;
        limit += 1u;
        ++ptr;
        --digits;
    }
    while (digits && *ptr) {
        uint32_t digit;
        if (*ptr >= '0' && *ptr <= '9') digit = *ptr - '0';
        else if (*ptr >= 'A' && *ptr <= 'F') digit = *ptr - 'A' + 10;
        else if (*ptr >= 'a' && *ptr <= 'f') digit = *ptr - 'a' + 10;
        else return 0;
        if (digit >= base || magnitude > (limit - digit) / base) return 0;
        magnitude = magnitude * base + digit;
        ++ptr;
        --digits;
    }
    if (negative && magnitude == (uint32_t)INT32_MAX + 1u) return INT32_MIN;
    return negative ? -(int32_t)magnitude : (int32_t)magnitude;
}
