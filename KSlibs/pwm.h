#ifndef PWM_H
#define PWM_H

#include "intmath.h"
#include "gpio.h"
#include "timer.h"

typedef struct {
	gpio_s pin;
	timer_s * timer;
	uint8_t compreg;
	//volatile uint16_t * tcomp;			// Timer compare register pointer
} pwm_s;

#ifdef __cplusplus
extern "C" {
#endif

void pwm_reset(pwm_s*);
void pwm_stop(pwm_s*);
void pwm_start(pwm_s*);

void pwm_set_duty(pwm_s*, uint16_t);
uint16_t pwm_get_duty(pwm_s*);

//void pwm_set_target(pwm_s*, uint16_t);

// All functions are inlined for maximum performance

extern inline
void pwm_reset(pwm_s* p){
	// Reset the pin
	gpio_set_ddr(p->pin);
	gpio_clr_pin(p->pin);
	// Reset duty to 0
	pwm_set_duty(p, 0);
}
extern inline
void pwm_stop(pwm_s* p){
	//Stop timer
	if (p->timer) timer_stop(p->timer);
	gpio_clr_pin(p->pin); 
}
extern inline
void pwm_start(pwm_s* p){
	//Start timer
	if (p->timer) timer_start(p->timer);
}
extern inline
void pwm_set_duty(pwm_s* p, unsigned int duty){
	// Set timer compare register
	timer_set_ocr(p->timer, p->compreg, duty);
}
extern inline
uint16_t pwm_get_duty(pwm_s* p){
	// Get timer compare register
	return timer_get_ocr(p->timer, p->compreg);
}

// PWM ISRs.

extern inline
void pwm_cmp(pwm_s* p){
	gpio_clr_pin(p->pin);
}
extern inline
void pwm_ovf(pwm_s* p){
	gpio_set_pin(p->pin);
}
#ifdef __cplusplus
}
#endif

#endif // PWM_H