#ifndef FORMAT_H
#define FORMAT_H

#include <stdint.h>
#include <stdbool.h>

void format_bin(char *dst, uint32_t value);
void format_hex(char *dst, uint32_t value);
void format_dec(char *dst, uint32_t value, bool is_signed);

#endif

