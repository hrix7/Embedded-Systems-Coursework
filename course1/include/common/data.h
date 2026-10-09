#ifndef COURSE_DATA_H
#define COURSE_DATA_H
#include <stdint.h>
#define BASE_2 2
#define BASE_10 10
#define BASE_16 16
#define ITOA_BUFFER_SIZE 34
/* Bases 2..16, uppercase A..F; signs supported in every base.
 * ptr must have 34 bytes for the worst case (INT32_MIN in binary).
 * Return count includes sign and NUL. Invalid base -> empty string/count 1;
 * NULL output -> count 0. */
uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);
/* digits is the maximum number of bytes read, including sign and optional NUL.
 * Stops at NUL. Accepts A..F/a..f. Invalid input/overflow returns 0. */
int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);
#endif
