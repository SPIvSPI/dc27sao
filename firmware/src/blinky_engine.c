#include <SI_EFM8BB1_Register_Enums.h>
#include <SI_EFM8BB1_Defs.h>
#include <stdio.h>
#include <stdlib.h>

#include "blinky_engine.h"
#include "animations.h"

#define FRAME_COUNT 3 // number of animation frames
#define PWM_SIZE 16 // number of ticks per PWM window

// Define to include snky.h for cipher challenge and such
//#define INCLUDE_CIPHER

#pragma OPTIMIZE(11)

uint32_t tick = 0;
uint8_t ticknybble = 0;
uint16_t windows_since_frame_start = 0;
uint8_t frame_number = 0;
uint8_t current_animation = 0;
led_frame* frames;

uint16_t animations_framecounts[ANIMATION_COUNT];
led_frame* animations[ANIMATION_COUNT];

void be_button() {
	current_animation++;
	if (current_animation >= ANIMATION_COUNT) {
		current_animation = 0;
	}
	frame_number = 0;
	windows_since_frame_start = 0;
	tick = 0; ticknybble = 0;
	frames = animations[current_animation];
}

void be_init_frames() {
	int i;

	// snky cipher challenge stuff
#ifdef INCLUDE_CIPHER
	#include "snky.h"
#endif

#ifdef NOSPY
	for (i=0; i<FRAME_COUNT; i++) {
		if(i==0) {
			frames[i].bytes[0] = 0xffff;
			frames[i].bytes[1] = 0x8888;
			frames[i].bytes[2] = 0x1111;
			frames[i].bytes[3] = 0x0200;
		} else if (i==1){
			frames[i].bytes[0] = 0x8888;
			frames[i].bytes[1] = 0x1111;
			frames[i].bytes[2] = 0xffff;
			frames[i].bytes[3] = 0x0200;
		} else if (i==2){
			frames[i].bytes[0] = 0x1111;
			frames[i].bytes[1] = 0xffff;
			frames[i].bytes[2] = 0x8888;
			frames[i].bytes[3] = 0x0200;
		}
	}
#endif
#ifdef WHITE
	// Call the init for each animation that's present
	// Also configure the count in animations.h
	// this is fugly but i am exhausted so whatever
	white_0();
	white_1();
	white_2();
#endif
#ifdef BLACK
	black_0();
	black_1();
	black_2();
#endif
	frames = animations[0];
}

uint8_t lit(uint8_t led_brightness) {
	return (ticknybble < led_brightness ? 0 : 1);
}

void be_do_tick() {
#ifdef NOSPY
	P0_B0 = lit(frames[frame_number].s.led1); // for debuggery
	P0_B1 = lit(frames[frame_number].s.led2);
	P0_B2 = lit(frames[frame_number].s.led3);
	P0_B3 = lit(frames[frame_number].s.led4);
	P0_B4 = lit(frames[frame_number].s.led5);
	P0_B5 = lit(frames[frame_number].s.led6);
	P0_B6 = lit(frames[frame_number].s.led7);
	P0_B7 = lit(frames[frame_number].s.led8);

	P1_B0 = lit(frames[frame_number].s.led9);

	P1_B2 = lit(frames[frame_number].s.led10);
	P1_B3 = lit(frames[frame_number].s.led11);
#endif
#ifdef WHITE
	P0_B0 = lit(frames[frame_number].s.led8); // Packing for white is Dn = ledn
	P0_B1 = lit(frames[frame_number].s.led7);
	P0_B2 = lit(frames[frame_number].s.led6);
	P0_B3 = lit(frames[frame_number].s.led5);
	P0_B4 = lit(frames[frame_number].s.led4);
	P0_B5 = lit(frames[frame_number].s.led3);
	P0_B6 = lit(frames[frame_number].s.led2);
	P0_B7 = lit(frames[frame_number].s.led1);

	P1_B0 = lit(frames[frame_number].s.led9);

	P1_B2 = lit(frames[frame_number].s.led10);
	P1_B3 = lit(frames[frame_number].s.led11); // not installed
#endif
#ifdef BLACK
	P0_B0 = lit(frames[frame_number].s.led8); // D11 packed into led8
 	P0_B1 = lit(frames[frame_number].s.led7); // D10 packed into led7
	P0_B2 = lit(frames[frame_number].s.led6); // D9 packed into led6
	P0_B3 = lit(frames[frame_number].s.led5); // D8 packed into led5
	P0_B4 = lit(frames[frame_number].s.led4); // D7 packed into led4
	P0_B5 = lit(frames[frame_number].s.led3); // D6 packed into led3
	P0_B6 = lit(frames[frame_number].s.led2); // D3 packed into led2; 3, 4, 5 connected
	P0_B7 = lit(frames[frame_number].s.led1); // D1 packed into led1; 1, 2 connected

	P1_B0 = lit(frames[frame_number].s.led9); // D12 packed into led9

	P1_B2 = lit(frames[frame_number].s.led10); // D13 packed into led10
	P1_B3 = lit(frames[frame_number].s.led11); // D14 packed into led11
#endif

	tick++;
	ticknybble = tick & 0xf;
	if (ticknybble % PWM_SIZE == 0) {
		windows_since_frame_start++;
	}
	if (windows_since_frame_start >= frames[frame_number].s.duration) {
		frame_number++;
		windows_since_frame_start = 0;
	}
	if (frame_number >= animations_framecounts[current_animation]) {
		frame_number = 0;
	}
}


