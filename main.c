#include <stdlib.h>
#include "framebuffer.h"
#include "shapes.h"
#define RGB(r, g, b) (b | g << 8 | r << 16 | 0xff << 24)
#define RGBA(r, g, b, a) (b | g << 8 | r << 16 | a << 24)
int main(int argc, char * * argv)
{
	uint32_t x, y;
	void *h_fb /* hardware graphics */, *v_fb /* virtual graphics */;
	x = 1176;
	y = 2300;
	if (argc == 3) { x = atoi(argv[1]); y = atoi(argv[2]); }
	v_fb = fb_create(x, y); // create a virtual buffer device
	h_fb = fb_open(x, y, NULL); // open hardware graphics
	sh_rectangle	(v_fb, x,   y,   0,  0,   RGB (255, 255, 255));	// set entire screen space white
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
	fb_flush(h_fb, v_fb);
	fb_close(h_fb); // close the hardware device
	fb_close(v_fb); // close the virtual device (destroy it)
	return 0;
}
