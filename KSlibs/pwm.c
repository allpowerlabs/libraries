// pwm.c

#include <avr/io.h>
#include "pwm.h"

#ifdef PWM0
pwm_s PWM0 = {&OCR1A};
#endif
#ifdef PWM1
pwm_s PWM1 = {&OCR1B};
#endif
#ifdef PWM2
pwm_s PWM2 = {&OCR1C};
#endif
#ifdef PWM3
pwm_s PWM3 = {&OCR3A};
#endif
#ifdef PWM4
pwm_s PWM4 = {&OCR3B};
#endif
#ifdef PWM5
pwm_s PWM5 = {&OCR3C};
#endif


void timer1_init(void) {
	// Zero count
	TCNT1 = 0;
	// Timer 1 control registers
	TCCR1A = 0 | _BV(WGM10); // Phase correct PWM
	TCCR1B = 0 | _BV(CS10);	// Clk/8
	TCCR1C = 0;
	TIMSK1 = 0;
#ifdef PWM0
	OCR1A = 0;
	TCCR1A |= _BV(COM1A1);
	DDRB |= _BV(DDB5);
#endif
#ifdef PWM1
	OCR1B = 0;
	TCCR1A |= _BV(COM1B1);
	DDRB |= _BV(DDB6);
#endif
#ifdef PWM2
	OCR1C = 0;
	TCCR1A |= _BV(COM1C1);
	DDRB |= _BV(DDB7);
#endif
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

void timer3_init(void) {
	// Zero count
	TCNT3 = 0;
	// Timer 1 control registers
	TCCR3A = 0 | _BV(WGM30); // Phase correct PWM
	TCCR3B = 0 | _BV(CS30);	// Clk/8
	TCCR3C = 0;
	TIMSK3 = 0;
#ifdef PWM3
	OCR3A = 0;
	TCCR3A |= _BV(COM3A1);
	DDRB |= _BV(DDE3);
#endif
#ifdef PWM4
	OCR3B = 0;
	TCCR3A |= _BV(COM3B1);
	DDRB |= _BV(DDE4);
#endif
#ifdef PWM5
	OCR3C = 0;
	TCCR3A |= _BV(COM3C1);
	DDRB |= _BV(DDE5);
#endif
}

void pwm_init(void) {
	timer1_init();
	timer3_init();
}