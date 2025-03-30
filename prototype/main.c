#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

enum NumBase {
	BIN = 2,
	DEC = 10,
	HEX = 16
};

void add_digit(uint32_t* value, unsigned char input, enum NumBase base);
void remove_digit(uint32_t* value, enum NumBase base);
void print_all(uint32_t value, enum NumBase base);

int main() {
	uint32_t value = 0;
	enum NumBase base = DEC;
	char input;

	printf("Welcome to Calculator.\nUse m for backspace.\nUse ',' '.' '/' for DEC, HEX, BIN respectively.\n\n");

	while ((input = getchar()) != 'q') {
		switch (input) {
			case '0' ... '9':
			case 'a' ... 'f':
				add_digit(&value, input, base);
				print_all(value, base);
				break;
			case 'm':
				remove_digit(&value, base);
				print_all(value, base);
				break;
			case ',':
				base = DEC;
				print_all(value, base);
				break;
			case '.':
				base = HEX;
				print_all(value, base);
				break;
			case '/':
				base = BIN;
				print_all(value, base);
				break;

		}
	}

	return 0;
}

static const char* nibble_str[] = {
	"0000", "0001", "0010", "0011",
	"0100", "0101", "0110", "0111",
	"1000", "1001", "1010", "1011",
	"1100", "1101", "1110", "1111"
};

void print_bin(uint32_t value) {
	bool started = false;

	for (int i = 7; i >= 0; i--) {
		uint8_t nibble = (value >> (i * 4)) & 0xF;

		if (nibble || started || i == 0) {
			printf("%s", nibble_str[nibble]);
			started = true;
			if (i > 0) putchar(' ');
		}
	}
}

void print_dec(uint32_t value) {
}

void print_all(uint32_t value, enum NumBase base) {
	printf("\n\n");

	if (base == DEC) {
		printf("\u2192DEC ");
	} else {
		printf(" DEC ");
	}
	printf("%d\n", value);

	if (base == HEX) {
		printf("\u2192HEX ");
	} else {
		printf(" HEX ");
	}
	printf("%X\n", value);

	if (base == BIN) {
		printf("\u2192BIN ");
	} else {
		printf(" BIN ");
	}
	print_bin(value);
	fputs("\n", stdout);
}

void add_digit(uint32_t* value, unsigned char input, enum NumBase base) {
	uint32_t digit;
	uint32_t temp;

	switch (input) {
		case '0' ... '9': digit = input - '0'; break;
		case 'a' ... 'f': digit = (input - 'a') + 10; break;
		default: return;
	}

	if (digit >= base) {
		return;
	}

	const uint32_t MAX = 0xFFFFFFFFu;
	if (*value > (MAX / base)) {
		// Multiplying would overflow
		return;
	}

	temp = (*value * base);
	if (temp > (MAX - digit)) {
		// Adding digit would overflow
		return;
	}

	*value = temp + digit;
	return;
}

void remove_digit(uint32_t* value, enum NumBase base) {
	switch (base) {
		case BIN:
			*value = *value >> 1;
			break;
		case HEX:
			*value = *value >> 4;
			break;
		case DEC:
			*value = *value / 10;
			break;
		default:
			*value = *value / base;
			break;
	}
	return;
}
