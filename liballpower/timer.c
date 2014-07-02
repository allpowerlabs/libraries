#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <limits.h>
#include "timer.h"

volatile timer_s * timer_head;

void timer_init() {
	// Make sure timer head pointer is NULL
	timer_head = 0;
	// Initialize AVR timer
	// Zero count
	TCNT4 = 0;
	// Enable interrupts
	TIMSK4 = 0
		| _BV(OCIE4A)		// Output compare A interrupt enable
		//| _BV(TOIE4)		// Overflow interrupt enable
	;
	// Timer control registers
	TCCR4A = 0;
	TCCR4B = 0
		//| _BV(CS42) 
		| _BV(CS41) 
		| _BV(CS40)
		| _BV(WGM42)		// Clear TC on match
	;  // clk/64 (4uS)
	TCCR4C = 0;
	// Set output compare registers
	OCR4AH = 0;
	OCR4AL = 250;
}
void timer_start(timer_s *t) {
	timer_s * u;
	// If there's no other timers, make this one the head
	if (!timer_head) timer_head = t;
	// Walk to the end of the list
	u = timer_head;
	while (u) {
		if (u == t) return; // Timer is already in the list
		if (u->next) u=u->next;
		else {
			u->next = t; // Found the end, add the new timer
			// Make sure t terminates the list
			t->next = 0;
			return;
		}
	}
}
void timer_stop(timer_s *t) {
	timer_s * u = timer_head;
	// Check for t at the head
	if (timer_head == t) {
		// Unlink t from the list
		timer_head = t->next;
		t->next = 0;
		return;
	}
	// Walk the list looking for t
	while (u) {
		if (u->next == t) {
			// Unlink t from the list
			u->next = t->next;
			t->next = 0;
			return;
		}
		else u = u->next;
	}
}
void timer_set(timer_s *t, unsigned long c) {
	t->count = c;
}
unsigned long timer_read(timer_s *t) {
	return t->count;
}

ISR(TIMER4_COMPA_vect) {
	timer_s * t = timer_head;
	while (t) {
		if (t->direction && (t->count < LONG_MAX)) t->count++;
		else if (t->count > 0) t->count--;
		t=t->next;
	}
}