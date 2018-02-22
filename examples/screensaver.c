#include <stdlib.h>
#include "../framebuffer.h"
#include "../shapes.h"
void screensaver_renderBox(void *v_fb)
{
	sh_rectangle	(v_fb, 150,   150,   0,  0,   RGB (255, 255, 255));	// set entire screen space white
	sh_square		(v_fb, 50,  0,   0,		 RGB (255, 0,	 0));	// red square at 0,0
	sh_square		(v_fb, 50,  50,  0,		 RGB (0,   255, 0));	// green square at 50,0
	sh_square		(v_fb, 50,  100, 0,		 RGB (0,   0,	 255));	// blue square at 100,0
	sh_square		(v_fb, 50,  0,   50,	 RGB (0,   255, 255));	// cyan square at 0,50
	sh_square		(v_fb, 50,  50,  50, 	 RGB (255, 0,	 255));	// magenta square at 50,50
	sh_square		(v_fb, 50,  100, 50, 	 RGB (255, 255, 0));	// yellow square at 100,50
	sh_rectangle	(v_fb, 37,  50,  0,  100, RGB (0,   0, 	 0));	// black rectangle at 0,100
	sh_rectangle	(v_fb, 38,  50,  37, 100, RGBA(0,   0, 	 0, 128));// black rectangle at 37,100 opacity 75%
	sh_rectangle	(v_fb, 37,  50,  75, 100, RGBA(0,   0, 	 0, 64));	// black rectangle at 75,100 opacity 25%
	sh_rectangle	(v_fb, 38,  50,  112,100, RGBA(0,   0, 	 0, 0));	// black rectangle at 112,100 opacity 0%
}
void screensaver_render(void *h_fb, void *v_fb, uint32_t x, uint32_t y, uint32_t rx, uint32_t ry)
{
	void *rfb; // rendering buffer
	rfb = fb_create(150, 150);
	screensaver_renderBox(rfb);
	fb_flush2_r(v_fb, rfb, rx, ry);
	fb_close(rfb);
	fb_flush(h_fb, v_fb);
	sh_rectangle	(v_fb, 150,   150,   rx,  ry,   RGB (255, 255, 255));	// set entire screen space white
}
void example_screensaver(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	uint32_t rx, ry;
	void *h_fb /* hardware graphics */, *v_fb /* virtual graphics */;
	v_fb = fb_create(x, y); // create a virtual buffer device
	h_fb = fb_open(x, y, NULL); // open hardware graphics
	sh_rectangle	(v_fb, x,   y,   0,  0,   RGB (255, 255, 255));	// set entire screen space white
	for (ry = 0; ry < h - 1; ++ry)
	{
		for (rx = 0; rx < (w - 150); ++rx) screensaver_render(h_fb, v_fb, x, y, rx, ry); // render forwards
		++ry; // move to next line
		for (rx = (w - 150); rx != 0; --rx) screensaver_render(h_fb, v_fb, x, y, rx, ry); // renderbackwards
	}
	fb_close(h_fb); // close the hardware device
	fb_close(v_fb); // close the virtual device (destroy it)
}
