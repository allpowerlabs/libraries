// pwm.c

#include <avr/io.h>
#include "pwm.h"

pwm_s PWM0 = {&OCR1AL};
pwm_s PWM1 = {&OCR1BL};
pwm_s PWM2 = {&OCR1CL};

void timer1_init(void) {
	// Set output compare registers
	OCR1AH = 0;
	OCR1AL = 0;
	// Zero count
	TCNT1H = 0;
	TCNT1L = 0;
	// Timer 1 control registers
	TCCR1A = 0
		| _BV(WGM10)		// Phase correct PWM
	//	| _BV(COM1A1)
		| _BV(COM1B1)
		| _BV(COM1C1)
	;
	TCCR1B = 0
		// | _BV(CS12) 
		// | _BV(CS11) 
		| _BV(CS10)
	;
	TCCR1C = 0;
	// Enable interrupts and start timer
	TIMSK1 |= 0
		//| _BV(OCIE1A)		// Output compare A interrupt enable
		//| _BV(TOIE1)		// Overflow interrupt enable
	;

	DDRB |= _BV(DDB5);
	DDRB |= _BV(DDB6);
	DDRB |= _BV(DDB7);
}

void timer2_init(void) {
	TCCR2A = 0;
	TCCR2B = 0
		| _BV(CS01);
	;
	TIMSK2 = 0
		| _BV(OCIE2A)
		| _BV(TOIE2)
	;
	
}

void pwm_init(void) {
	timer1_init();
}