#ifndef TIMER_H
#define TIMER_H

// Note: it would be really great to use ATOMIC_BLOCK to turn off interrupts
// around these register accesses, but unfortunately we'd have to switch
// to compiling this with C99, which isn't supported by the Arduino IDE.
//#include <util/atomic.h>
#include <avr/interrupt.h>

#define TIMER_COMPA 0
#define TIMER_COMPB 1
#define TIMER_COMPC 2

#define TIMER_WGM_MASK_A 0x02
#define TIMER_WGM_MASK_B 0x18
#define TIMER_WGM_NORMAL 0
#define TIMER_WGM_CTC 

#define TIMER_COM_MASK 0xFC
#define TIMER_COM_NORMAL 0

#define TIMER_CLK_MASK 0x07

typedef uint8_t timer_t;
typedef void (* timer_int_f)();

typedef struct {
	timer_t	t;			// Timer identity
/* 	
	timer_int_f cmp;	// Compare match vector
	timer_int_f ovf;	// Overflow vector
	union {
		struct {
			uint8_t	wgm0:1;		// Waveform generation mode
			uint8_t	wgm1:1;		// Waveform generation mode
			uint8_t comc0:1;	// Compare C output mode
			uint8_t comc1:1;	// Compare C output mode
			uint8_t comb0:1;	// Compare B output mode
			uint8_t comb1:1;	// Compare B output mode
			uint8_t coma0:1;	// Compare A output mode
			uint8_t coma1:1;	// Compare A output mode
		} bit;
		uint8_t reg;
	} tccra;
	union {
		struct {
			uint8_t cs0:1;		// Clock select
			uint8_t cs1:1;		// Clock select
			uint8_t cs2:1;		// Clock select
			uint8_t	wgm2:1;		// Waveform generation mode
			uint8_t	wgm3:1;		// Waveform generation mode
			uint8_t	rsvd:1;		// Reserved
			uint8_t	ices:1;		// Input capture edge select
			uint8_t icnc:1;		// Input capture noise canceller
		} bit;
		uint8_t reg;
	} tccrb;
	union {
		struct {
			uint8_t rsvd:5;
			uint8_t foca:1;
			uint8_t focb:1;
			uint8_t focc:1;
		} bit;
		uint8_t reg;
	} tccrc;
	 */
} timer_s;

extern timer_s timer0;
extern timer_s timer1;
extern timer_s timer2;
extern timer_s timer3;
extern timer_s timer4;
extern timer_s timer5;

#ifdef __cplusplus
extern "C" {
#endif

void timer_init(timer_s *);

extern inline
void timer_reset(timer_s *t) {
	//ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		// Zero output compare registers
		OCR5AH = 0;
		OCR5AL = 0;
		// Zero count
		TCNT5H = 0;
		TCNT5L = 0;
	//}
}
extern inline 
void timer_stop(timer_s *t) {
	//ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		// Stop timer and disable interrupts
		TCCR5B = 0;				// Disconnect prescaler
		TIMSK5 &= ~_BV(OCIE5A)	// Output compare A interrupt disable
			& ~_BV(TOIE5)		// Overflow interrupt disable
		;
	//}
}
extern inline 
void timer_start(timer_s *t) {
	//ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		// Enable interrupts and start timer
		TIMSK5 |= _BV(OCIE5A)	// Output compare A interrupt enable
			| _BV(TOIE5)		// Overflow interrupt enable
		;
		TCCR5B = 0
			//| _BV(CS52) 
			//| _BV(CS51) 
			| _BV(CS50)
			;  //Normal mode, clk/64 (4uS)
	//}
}

void timer_set_ocr(timer_t, uint8_t);
uint16_t timer_get_ocr(timer_t, uint8_t);


#ifdef __cplusplus
}
#endif

#endif	// TIMER_H