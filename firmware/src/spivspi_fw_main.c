#include <SI_EFM8BB1_Register_Enums.h>
#include <SI_EFM8BB1_Defs.h>

#include "blinky_engine.h"
#include "animations.h"

#define CLK_DIVIDER CLKSEL_CLKDIV__SYSCLK_DIV_1
#define SYSCLK 24500000/1  // SYSCLK frequency in Hz
#define TICK_RATE_HZ 16000 // 16-step PWM, so PWM rate of 1KHz; 1ms per frame
#define DEBOUNCE_MS 50

#pragma OPTIMIZE(11)

int a = 0;
uint16_t debounce = 0;
uint8_t but_lockout = 0;

void Port_Init (void);
void Timer2_Init_Hz (int counts);

// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ).
void SiLabs_Startup (void)
{
	// Disable the watchdog with magic sequence
	// WDTCN = 0xDE;
	// WDTCN = 0xAD;
	// WDTCN = 0xA5; // do this to enable and periodically thereafter to poke the dog

	CLKSEL = CLKSEL_CLKSL__HFOSC | CLK_DIVIDER;
}

int main (void)
{
	Port_Init();
	Timer2_Init_Hz(TICK_RATE_HZ);
	be_init_frames();
	IE_EA = 1; // Enable interrupts
	while (1) {
	   PCON0 |= PCON0_IDLE__IDLE; // set idle mode
	   PCON0 = PCON0; // 3-cycle dummy instruction (see Ref Manual: 7.3 Idle Mode)
	}
}

void Port_Init (void)
{
	// Configure crossbar and ports
	// use all of ports 0.0-7 1.0-3 except 1.1, which is button

	P0SKIP |= 0xff;  // Don't assign any peripherals to P0
	P0MDIN |= 0xff;  // Set P0 to digital mode
	P0MDOUT |= 0x00; // Set P0 to open-drain

	P1SKIP |= 0x0f; // Don't assign any peripherals to P1
	P1MDIN |= 0x0f; // Set P1 to digital mode
	P1MDOUT = 0x00; // Set P1 to open-drain
	P1_B1 = 1;      // Set P1.1 to enable input

	XBR2 = 0x40;    // Enable crossbar and pull-ups
}

void Timer2_Init_Hz (int hz)
{
	TMR2CN0 = 0x00; // Stop Timer2; Clear TF2
	CKCON0 |= 0x10; // Timer2 clocked by SYSCLK

	TMR2RL = 65536 - (SYSCLK / hz); // Set timer reload value
	TMR2 = 0xffff;                  // Ready to overflow, will reload on start
	IE_ET2 = 1;                     // Enable Timer2 interrupts
	TMR2CN0_TR2 = 1;                // Start Timer2
}

SI_INTERRUPT (TIMER2_ISR, TIMER2_IRQn)
{
	TMR2CN0_TF2H = 0; // Clear Timer2 interrupt flag
	WDTCN = 0xA5; // Poke the dog

	// Read button state
	if(P1_B1 == 0) {
	   if (debounce > DEBOUNCE_MS * 16) {
		   if (!but_lockout) {
			   but_lockout = 1;
			   be_button();
		   }
	   } else {
		   debounce++;
	   }
	} else {
		if (debounce == 1) but_lockout = 0;
		if (debounce > 0) debounce--;
	}

	be_do_tick();
}

