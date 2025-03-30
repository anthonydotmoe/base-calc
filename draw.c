#include <graph.h>
#include <string.h>
#include "draw.h"
#include "format.h"

//TODO: Consider not using a function pointer

extern bool g_signed;  // from main.c

static const uint32_t test_number = 0x80070057;

void draw_layout_ti89(void) {
	char buf[40];
	short num_x;

	// Clear screen areas first
	FontSetSys(F_4x6);
	DrawStr(0, 60, "HEX", A_NORMAL);
	DrawStr(0, 68, "DEC", A_NORMAL);
	DrawStr(0, 76, "BIN", A_NORMAL);

	ScrRectFill(&(SCR_RECT){{48, 20, 159, 30}}, ScrRect, A_REVERSE);
	ScrRectFill(&(SCR_RECT){{16, 59, 159, 82}}, ScrRect, A_REVERSE);

	// Big decimal number
	format_dec(buf, test_number, g_signed);
	FontSetSys(F_8x10);
	num_x = 160 - (8 * strlen(buf));
	DrawStr(num_x, 20, buf, A_NORMAL);

	// Smaller conversions
	FontSetSys(F_6x8);
	format_hex(buf, test_number);
	DrawStr(16, 59, buf, A_NORMAL);

	format_dec(buf, test_number, g_signed);
	DrawStr(16, 67, buf, A_NORMAL);

	FontSetSys(F_4x6);
	format_bin(buf, test_number);
	DrawStr(16, 76, buf, A_NORMAL);
}

void draw_layout_ti92(void) {
	char buf[40];
	short num_x;

	// Clear screen areas first
	FontSetSys(F_4x6);
	DrawStr(0, 60, "HEX", A_NORMAL);
	DrawStr(0, 68, "DEC", A_NORMAL);
	DrawStr(0, 76, "BIN", A_NORMAL);

	ScrRectFill(&(SCR_RECT){{128, 20, 239, 30}}, ScrRect, A_REVERSE);
	ScrRectFill(&(SCR_RECT){{16, 59, 159, 82}}, ScrRect, A_REVERSE);

	// Big decimal number
	format_dec(buf, test_number, g_signed);
	FontSetSys(F_8x10);
	num_x = 240 - (8 * strlen(buf));
	DrawStr(num_x, 20, buf, A_NORMAL);

	// Smaller conversions
	FontSetSys(F_6x8);
	format_hex(buf, test_number);
	DrawStr(16, 59, buf, A_NORMAL);

	format_dec(buf, test_number, g_signed);
	DrawStr(16, 67, buf, A_NORMAL);

	FontSetSys(F_4x6);
	format_bin(buf, test_number);
	DrawStr(16, 76, buf, A_NORMAL);
}

