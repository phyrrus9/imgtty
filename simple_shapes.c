#include "shapes.h"
void fb_pri_setpixel(void *fb, fb_word x, fb_word y, fb_word clr);
void sh_rectangle(void *fb, fb_word xsize, fb_word ysize, fb_word x, fb_word y, fb_word color)
{
    fb_word px, py;
    void *dr = fb_create(xsize, ysize);
    for (py = 0; py < ysize; ++py) for (px = 0; px < xsize; ++px) fb_pri_setpixel(dr, px, py, color);
    fb_flush2(fb, dr, x, y);
    fb_close(dr);
}
void sh_square(void *fb, fb_word size, fb_word x, fb_word y, fb_word color) { sh_rectangle(fb, size, size, x, y, color); }
