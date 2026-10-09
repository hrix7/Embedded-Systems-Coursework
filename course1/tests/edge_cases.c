/* Independent checks; standard memory/string routines are test oracles only. */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "memory.h"
#include "data.h"
#include "stats.h"
int main(void)
{
    unsigned int cases = 0;
    uint8_t a[64], b[64], separate[64], text[ITOA_BUFFER_SIZE];
    const int32_t values[] = {INT32_MIN, INT32_MAX, -4096, -1, 0, 1, 123456};
    size_t n, src, dst, i;
    uint32_t base;
    for (n = 0; n <= 32; ++n) {
        for (src = 0; src + n <= 64; ++src) {
            for (dst = 0; dst + n <= 64; ++dst) {
                for (i = 0; i < 64; ++i) a[i] = b[i] = (uint8_t)i;
                memmove(b + dst, b + src, n);
                assert(my_memmove(a + src, a + dst, n) == a + dst);
                assert(memcmp(a, b, 64) == 0);
                ++cases;
            }
        }
        for (i = 0; i < 64; ++i) a[i] = b[i] = (uint8_t)i;
        assert(my_memcopy(a, separate, n) == separate);
        assert(memcmp(a, separate, n) == 0);
        assert(my_memmove(a, separate, n) == separate);
        assert(memcmp(a, separate, n) == 0);
        assert(my_reverse(a, n) == a);
        for (i = 0; i < n; ++i) assert(a[i] == b[n-i-1]);
        assert(memcmp(a+n,b+n,64-n) == 0);
        assert(my_memset(a,n,0xA5) == a);
        for (i = 0; i < n; ++i) assert(a[i] == 0xA5);
        assert(my_memzero(a,n) == a);
        for (i = 0; i < n; ++i) assert(a[i] == 0);
    }
    for (base = 2; base <= 16; ++base) {
        for (i = 0; i < sizeof(values)/sizeof(*values); ++i) {
            uint8_t count = my_itoa(values[i], text, base);
            char expected[ITOA_BUFFER_SIZE];
            char *end = expected + sizeof(expected);
            uint64_t magnitude = values[i] < 0 ? -(int64_t)values[i] : values[i];
            *--end = 0;
            do {
                *--end = "0123456789ABCDEF"[magnitude % base];
                magnitude /= base;
            } while (magnitude);
            if (values[i] < 0) *--end = '-';
            assert(strcmp((char *)text,end) == 0);
            assert(count == strlen(end)+1);
            assert(my_atoi(text,count,base) == values[i]);
            assert(my_atoi(text,count-1,base) == values[i]);
        }
    }
    assert(my_atoi((uint8_t *)"-80000000",9,16) == INT32_MIN);
    assert(my_atoi((uint8_t *)"7fffffff",8,16) == INT32_MAX);
    assert(my_atoi((uint8_t *)"2147483648",10,10) == 0);
    assert(my_atoi((uint8_t *)"-2147483649",11,10) == 0);
    assert(my_atoi((uint8_t *)"2",1,2) == 0);
    assert(my_atoi(NULL,0,10) == 0);
    assert(my_itoa(1,text,17) == 1 && *text == 0);
    assert(my_itoa(1,NULL,10) == 0);
    assert(reserve_words(SIZE_MAX) == NULL);
    assert(reserve_words(0) == NULL);
    { int32_t *words = reserve_words(3); assert(words); words[2] = INT32_MIN; free_words(words); }
    free_words(NULL);
    { unsigned char data[] = {9,1,7,3};
      assert(find_mean(data,4) == 5); assert(find_median(data,4) == 5);
      assert(find_minimum(data,4) == 1); assert(find_maximum(data,4) == 9);
      assert(data[0] == 9 && data[1] == 7 && data[2] == 3 && data[3] == 1);
      assert(find_median(data,3) == 7); assert(find_mean(NULL,0) == 0); }
    printf("PASS: %u memory-overlap cases; all bases 2..16 and signed limits; allocation, reverse, fill, copy and statistics checks.\n", cases);
    return 0;
}
