#include <avr/interrupt.h>
#include <avr/io.h>
#include "timer.h"

timer_s timer1; //= {0, 0, 0, 0, 0, 0};
timer_s timer3; // = {0, 0, 0, 0, 0, 0};
timer_s timer4; // = {0, 0, 0, 0, 0, 0};
timer_s timer5; // = {0, 0, 0, 0, 0, 0};

// Interrupt service routines
// ISR(TIMER5_COMPA_vect) {
	// timer5.cmp();
// }
// ISR(TIMER5_OVF_vect) {
	// timer5.ovf();
// }

void timer_init(timer_s *t) {
	// Timer 5 control registers
//	TCCR5A = 0;
//	TCCR5C = 0;
	// Timer 5 interrupt mask
}