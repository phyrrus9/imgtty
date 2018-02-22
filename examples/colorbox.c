#include <stdlib.h>
#include "../framebuffer.h"
#include "../shapes.h"

void example_colorbox(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	void *h_fb /* hardware graphics */, *v_fb /* virtual graphics */;
	v_fb = fb_create(x, y); // create a virtual buffer device
	h_fb = fb_open(x, y, NULL); // open hardware graphics
	sh_rectangle	(v_fb, 600,  600,  100,   0,   RGB (255, 255, 255   ));	// set draw box to white (for opacity testing)
	sh_square		(v_fb, 200,  100,  0,		 RGB (255, 0,	 0     ));	// red square
	sh_square		(v_fb, 200,  300,  0,		 RGB (0,   255, 0     ));	// green square
	sh_square		(v_fb, 200,  500,  0,		 RGB (0,   0,	 255   ));	// blue square
	sh_square		(v_fb, 200,  100,  200,	 	 RGB (0,   255, 255   ));	// cyan square
	sh_square		(v_fb, 200,  300,  200, 	 	 RGB (255, 0,	 255   ));	// magenta square
	sh_square		(v_fb, 200,  500,  200, 	 	 RGB (255, 255, 0     ));	// yellow square
	sh_rectangle	(v_fb, 148,  200,  100,  400,  RGB (0,   0, 	 0     ));	// black rectangle
	sh_rectangle	(v_fb, 152,  200,  248,  400,  RGBA(0,   0, 	 0, 128));	// black rectangle opacity 75%
	sh_rectangle	(v_fb, 148,  200,  400,  400,  RGBA(0,   0, 	 0, 64));		// black rectangle opacity 25%
	sh_rectangle	(v_fb, 152,  200,  548,  400,  RGBA(0,   0, 	 0, 0));		// black rectangle opacity  0%
	fb_flush(h_fb, v_fb);
	fb_close(h_fb); // close the hardware device
	fb_close(v_fb); // close the virtual device (destroy it)
}
