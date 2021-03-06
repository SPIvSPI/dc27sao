#include "blinky_engine.h"
#include "animations.h"

// frameCount = 26
// animationId = 2

extern led_frame* animations[];
extern uint16_t animations_framecounts[];
white_2() {
	code led_frame aniframes[] = {
		{ 0x00ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x00ff, 0xffff, 0x00ff, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x00ff, 0x01f4 },
		{ 0x00ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x00ff, 0x01f4 },
		{ 0x00ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x0fff, 0xfff0, 0x00ff, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x00ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0xffff, 0xffff, 0x000f, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x00ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0xf0ff, 0xffff, 0x00ff, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x00ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x00ff, 0xffff, 0x000f, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x00ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x0fff, 0xfff0, 0x00ff, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x00ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0xf0ff, 0xfff0, 0x00ff, 0x01f4 },
		{ 0x00ff, 0xfff0, 0x000f, 0x01f4 },
		{ 0x0033, 0x3330, 0x0003, 0x07d0 }
	};
	animations_framecounts[2] = 26;
	animations[2] = aniframes;
}
