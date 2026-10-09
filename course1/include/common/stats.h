#ifndef COURSE_STATS_H
#define COURSE_STATS_H
/* Nonempty byte arrays required for statistics; empty/NULL returns zero.
 * sort_array sorts descending in place; find_median also sorts in place.
 * Mean and even-length median use integer truncation. */
void print_statistics(unsigned char *data, unsigned int length);
void print_array(unsigned char *data, unsigned int length);
unsigned char find_median(unsigned char *data, unsigned int length);
unsigned char find_mean(unsigned char *data, unsigned int length);
unsigned char find_maximum(unsigned char *data, unsigned int length);
unsigned char find_minimum(unsigned char *data, unsigned int length);
void sort_array(unsigned char *data, unsigned int length);
#endif
