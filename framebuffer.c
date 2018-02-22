#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "framebuffer.h"

struct framebuffer
{
	fb_word xres, yres;
	void *buffer;
	uint8_t hardware : 1; // set this bit if it is a hardware buffer
};

void *fb_create(fb_word xres, fb_word yres)
{
	void *buffer;
	struct framebuffer *fb = NULL;
	if ((buffer = malloc(xres * yres * sizeof(fb_word))) != NULL)
	{
		fb = malloc(sizeof(struct framebuffer)); fb->buffer = buffer;
		fb->xres = xres; fb->yres = yres; fb->hardware = 0;
	}
	return fb;
}
void *fb_open(fb_word xres, fb_word yres, const char *path)
{
	void *ret;
	const char *p = path == NULL ? "/dev/fb0" : path;
	struct framebuffer *retfb = NULL;
	FILE *f = fopen(p, "wb+");
	if ((ret = mmap(0, xres * yres, PROT_WRITE, MAP_SHARED, fileno(f), 0)) != NULL)
	{
		retfb = malloc(sizeof(struct framebuffer));
		retfb->buffer = ret; retfb->hardware = 1;
		retfb->xres = xres; retfb->yres = yres;
	}
	fclose(f);
	return retfb;
}
fb_word fb_pri_blend(fb_word o, fb_word n)
{
	return
		(fb_word)((((n & 0x00FF0000) >> 16) * (((n & 0xFF000000) >> 24) / (double)255)) + ((1 - (((n & 0xFF000000) >> 24) / (double)255)) * ((o & 0x00FF0000) >> 16)))		|
		(fb_word)((((n & 0x0000FF00) >>  8) * (((n & 0xFF000000) >> 24) / (double)255)) + ((1 - (((n & 0xFF000000) >> 24) / (double)255)) * ((o & 0x0000FF00) >>  8))) << 8	|
		(fb_word)((((n & 0x000000FF)      ) * (((n & 0xFF000000) >> 24) / (double)255)) + ((1 - (((n & 0xFF000000) >> 24) / (double)255)) * ((o & 0x000000FF)      ))) << 16	;
}
void fb_setpixel(void *fb, fb_word x, fb_word y, fb_word clr)
{
	fb_word pixel = y * ((struct framebuffer *)fb)->xres + x;
	fb_word *buf = ((struct framebuffer *)fb)->buffer;
	buf[pixel] = fb_pri_blend(buf[pixel], clr);
}
void fb_pri_setpixel(void *fb, fb_word x, fb_word y, fb_word clr)
{
	fb_word pixel = y * ((struct framebuffer *)fb)->xres + x;
	fb_word *buf = ((struct framebuffer *)fb)->buffer;
	buf[pixel] = clr;
}
void fb_flush(void *dst, const void *src)
{
	const fb_word src_sz = ((struct framebuffer *)src)->xres * ((struct framebuffer *)src)->yres;
	const fb_word dst_sz = ((struct framebuffer *)dst)->xres * ((struct framebuffer *)dst)->yres;
	memcpy(((struct framebuffer *)dst)->buffer, ((struct framebuffer *)src)->buffer, src_sz > dst_sz ? dst_sz : src_sz);
}
void fb_flush2(void *dst, const void *src, fb_word xoff, fb_word yoff)
{ fb_flush3(dst, src, xoff, yoff, ((struct framebuffer *)src)->xres, ((struct framebuffer *)src)->yres); }
void fb_flush3(void *dst, const void *src, fb_word xoff, fb_word yoff, fb_word xmax, fb_word ymax)
{
	register fb_word x, y;
	struct framebuffer *dfb = dst;
	const struct framebuffer *sfb = src;
	fb_word *p_dfb = dfb->buffer;
	const fb_word *p_sfb = sfb->buffer;
	if (dfb->hardware) return; // can't write like this to a hardware buffer
	for (y = 0; y < sfb->yres && y + yoff < dfb->yres && y < ymax; ++y)
		for(x = 0; x < sfb->xres && (x + xoff < dfb->xres) && x < xmax; ++x)
			p_dfb[(y + yoff) * dfb->xres + (x + xoff)] = fb_pri_blend(p_dfb[(y + yoff) * dfb->xres + (x + xoff)], p_sfb[y * sfb->xres + x]);
}
void fb_clear(void *fb) { memset(((struct framebuffer *)fb)->buffer, 0, ((struct framebuffer *)fb)->xres * ((struct framebuffer *)fb)->yres); }
void fb_close(void *fb)
{
	if (((struct framebuffer *)fb)->buffer == NULL) return;
	if (((struct framebuffer *)fb)->hardware) munmap(((struct framebuffer *)fb)->buffer, ((struct framebuffer *)fb)->xres * ((struct framebuffer *)fb)->yres);
	else free(((struct framebuffer *)fb)->buffer);
	((struct framebuffer *)fb)->buffer = NULL; ((struct framebuffer *)fb)->xres = ((struct framebuffer *)fb)->yres = 0;
}
