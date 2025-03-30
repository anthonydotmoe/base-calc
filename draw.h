#ifndef DRAW_H
#define DRAW_H

// Externally visible draw functions
extern void (*draw_layout)(void);  // set by detect_hardware()

void draw_layout_ti89(void);
void draw_layout_ti92(void);

#endif

