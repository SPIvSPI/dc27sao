#ifndef BLINKY_ENGINE_H_
#define BLINKY_ENGINE_H_

#include <SI_EFM8BB1_Register_Enums.h>
#include <SI_EFM8BB1_Defs.h>

typedef uint8_t u8;
typedef uint16_t u16;

typedef struct frame_struct {
	u8 led3 : 4;      // white D3, black D6
	u8 led4 : 4;      // white D4, black D7
	u8 led1 : 4;      // white D1, black D1 + D2
	u8 led2 : 4;      // white D2, black D3 + D4 + D5

	u8 led7 : 4;      // white D7, black D10
	u8 led8 : 4;      // white D8, black D11
	u8 led5 : 4;      // white D5, black D8
	u8 led6 : 4;      // white D6, black D9

	u8 led11 : 4;     //          , black D14
	u8 pad : 4;       // padding for alignment
	u8 led9 : 4;      // white D9, black D12
	u8 led10 : 4;     // white D10, black D13

	u16 duration : 16;  // duration in PWM windows
} frame_struct;

typedef union led_frame {
	u16 bytes[4];
	frame_struct s;
} led_frame;

void be_init_frames();
void be_do_tick();
void be_button();

#endif /* BLINKY_ENGINE_H_ */
