#include "format.h"

static const char* nibble_str[] = {
	"0000", "0001", "0010", "0011",
	"0100", "0101", "0110", "0111",
	"1000", "1001", "1010", "1011",
	"1100", "1101", "1110", "1111"
};

void format_bin(char *dst, uint32_t value) {
	bool started = false;
	int pos = 0;
	int i;

	dst[0] = '\0';

	for (i = 7; i >= 0; i--) {
		uint8_t nibble = (value >> (4 * i)) & 0xF;
		if (nibble || started || i == 0) {
			const char *bits = nibble_str[nibble];
			int j;
			for (j = 0; j < 4; j++) {
				dst[pos++] = bits[j];
			}

			started = true;

			// Add a space if not the last nibble
			if (i > 0) {
				dst[pos++] = ' ';
			}
		}
	}

	dst[pos] = '\0';
}

void format_hex(char *dst, uint32_t value) {
	bool started = false;
	int pos = 0;
	int i;

	for (i = 7; i >= 0; i--) {
		uint8_t nibble = (value >> (4 * i)) & 0xF;

		if (nibble || started || i == 0) {
			dst[pos++] = "0123456789ABCDEF"[nibble];
			started = true;
		}

		if (i == 4 && started) {
			dst[pos++] = ' ';
		}
	}

	if (!started) {
		dst[pos++] = '0';
	}

	dst[pos] = '\0';
}


void format_dec(char *dst, uint32_t value, bool is_signed) {
	char tmp[24]; // enough space
	char *p = tmp + 23;
	*p = '\0';

	bool negative = false;
	uint32_t val;

	// Handle negative
	if (is_signed && ((int32_t)value) < 0) {
		negative = true;
		val = (uint32_t)(-(int32_t)value);
	} else {
		val = value;
	}

	int digit_count = 0;
	if (val == 0) {
		*--p = '0';
		digit_count = 1;
	}

	// Convert to decimal, inserting commas every 3 digits (optional)
	while (val > 0) {
		if (digit_count > 0 && digit_count % 3 == 0) {
			*--p = ',';
		}
		*--p = '0' + (val % 10);
		val /= 10;
		digit_count++;
	}

	if (negative) {
		*--p = '-';
	}

	// Copy into dst
	while (*p) {
		*dst++ = *p++;
	}
	*dst = '\0';
}

