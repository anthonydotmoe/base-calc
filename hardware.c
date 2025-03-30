#include <flash.h>
#include "hardware.h"
#include "draw.h"  // because we need to set draw_layout pointer

// The pointer to the appropriate draw function.
void (*draw_layout)(void) = NULL;

// Returns 1 = TI-92 Plus, 3 = TI-89, 8 = Voyage 200
unsigned long detect_hardware() {
	const HARDWARE_PARM_BLOCK *hpb = FL_getHardwareParmBlock();
	unsigned long hwID = hpb->hardwareID;

	// First check if the screen size is available
	if (hpb->len == sizeof(HARDWARE_PARM_BLOCK)) {
		// Use this to detect
		switch (hpb->LCDBitsWide) {
			case 240:
				draw_layout = draw_layout_ti92;
				break;
			case 160:
				draw_layout = draw_layout_ti89;
				break;
			default:
				draw_layout = NULL;
				break;
		}
	}

	// Second check by hardware ID
	switch (hwID) {
		case 1:
			draw_layout = draw_layout_ti92;
			break;
		case 3:
			draw_layout = draw_layout_ti89;
			break;
		default:
			// draw_layout stays NULL if it was never set
			break;
	}

	return hwID;
}

