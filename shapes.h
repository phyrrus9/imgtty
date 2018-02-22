#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include "framebuffer.h"

void sh_rectangle(void *fb, fb_word xsize, fb_word ysize, fb_word x, fb_word y, fb_word color);
void sh_square(void *fb, fb_word size, fb_word x, fb_word y, fb_word color);

#endif // SHAPES_H_INCLUDED
