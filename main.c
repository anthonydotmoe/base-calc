#define SAVE_SCREEN
#define USE_TI89
#define USE_V200
#define MIN_AMS 200

#include <args.h>
#include <flash.h>
#include <graph.h>
#include <kbd.h>

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "hardware.h"
#include "draw.h"
#include "format.h"

bool g_signed = true;

void _main(void) {
	unsigned long hwID;
	short key;

	// Detect hardware and set up the global draw_layout pointer
	hwID = detect_hardware();
	if (draw_layout == NULL) {
		// TODO: Error handling here
		return;
	}

	ClrScr();

	do {
		draw_layout();
		key = ngetchx();

		if (key == KEY_NEGATE) {
			g_signed ^= 1;
		}

	} while (key != KEY_ESC && key != KEY_QUIT);
}

