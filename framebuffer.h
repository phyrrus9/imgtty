#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#define RGB(r, g, b) (b | g << 8 | r << 16 | 0xff << 24)
#define RGBA(r, g, b, a) (b | g << 8 | r << 16 | a << 24)

#include <stdint.h>
typedef uint32_t fb_word;

void *fb_create(fb_word xres, fb_word yres); // create a virtual buffer device
void *fb_open(fb_word xres, fb_word yres, const char *path); // open a buffer device
void fb_setpixel(void *fb, fb_word x, fb_word y, fb_word clr); // set pixel on buffer device
void fb_flush(void *dst, const void *src); // flush state of src into dst
void fb_flush2(void *dst, const void *src, fb_word xoff, fb_word yoff); // flush state of src to dst starting at (xoff, yoff)
void fb_flush2_r(void *dst, const void *src, fb_word xoff, fb_word yoff); // flush state of src to dst starting at (xoff, yoff), raw
void fb_flush3(void *dst, const void *src, fb_word xoff, fb_word yoff, fb_word xmax, fb_word ymax); // flush with offset (xoff, yoff) with limits
void fb_flush3_r(void *dst, const void *src, fb_word xoff, fb_word yoff, fb_word xmax, fb_word ymax); // flush with offset (xoff, yoff) with limits, raw
void fb_clear(void *fb); // clear the state of a buffer device
void fb_close(void *fb); // close a buffer device

#endif // FRAMEBUFFER_H
