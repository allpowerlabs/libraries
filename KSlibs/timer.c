#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include "timer.h"

#ifndef NULL
#define NULL 0
#endif

const timer_s timer0 = {
	TIMER_TYPE_0,
	&TCCR0A,
	&TCCR0B,
	NULL,
	&TCNT0,
	NULL,
	&OCR0A,
	NULL,
	&OCR0B,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&TIMSK0,
	&TIFR0,
	NULL
};

const timer_s timer2 = {
	TIMER_TYPE_2,
	&TCCR2A,
	&TCCR2B,
	NULL,
	&TCNT2,
	NULL,
	&OCR2A,
	NULL,
	&OCR2B,
	NULL,
	NULL,
	NULL,
	NULL,
	&ASSR,
	&TIMSK2,
	&TIFR2,
	&GTCCR
};
const timer_s timer1; //= {0, 0, 0, 0, 0, 0};
const timer_s timer2;
const timer_s timer3; // = {0, 0, 0, 0, 0, 0};
const timer_s timer4; // = {0, 0, 0, 0, 0, 0};
const timer_s timer5; // = {0, 0, 0, 0, 0, 0};

void timer_init(const timer_s *t) {
}

void timer_set_ocr(const timer_s * timer, unsigned char ocr, uint16_t value) {
	switch (timer->type) {
		case TIMER_TYPE_0:
			switch (ocr) {
				case TIMER_COMPA:
					*timer->ocral = value;
					break;
				case TIMER_COMPB:
					*timer->ocrbl = value;
					break;
			}
			break;
		case TIMER_TYPE_1:
			switch (ocr) {
				case TIMER_COMPA:
					*timer->ocrah = value >> 8;
					*timer->ocral = value;
					break;
				case TIMER_COMPB:
					*timer->ocrbh = value >> 8;
					*timer->ocrbl = value;
					break;
				case TIMER_COMPC:
					*timer->ocrch = value >> 8;
					*timer->ocrcl = value;
					break;
			}
			break;
		case TIMER_TYPE_2:
			switch (ocr) {
				case TIMER_COMPA:
					*timer->ocral = value;
					break;
				case TIMER_COMPB:
					*timer->ocrbl = value;
					break;
			}
			break;
	}
}

uint16_t timer_get_ocr(const timer_s * timer, unsigned char ocr) {
	switch (timer->type) {
		case TIMER_TYPE_0:
			switch (ocr) {
				case TIMER_COMPA:
					return *timer->ocral;
					break;
				case TIMER_COMPB:
					return *timer->ocrbl;
					break;
			}
			break;
		case TIMER_TYPE_1:
			switch (ocr) {
				case TIMER_COMPA:
					return *timer->ocral;
					break;
				case TIMER_COMPB:
					return *timer->ocrbl;
					break;
				case TIMER_COMPC:
					return *timer->ocrcl;
					break;
			}
			break;
		case TIMER_TYPE_2:
			switch (ocr) {
				case TIMER_COMPA:
					return *timer->ocral;
					break;
				case TIMER_COMPB:
					return *timer->ocrbl;
					break;
			}
			break;
	}
}

/* 
	switch (timer->type) {
		case TIMER_TYPE_0:
			break;
		case TIMER_TYPE_1:
			break;
		case TIMER_TYPE_2:
			break;
	} 
*/