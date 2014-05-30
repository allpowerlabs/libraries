#ifndef PWM_H
#define PWM_H

#include <stdint.h>
//#include "intmath.h"
//#include "timer.h"
//#include "gpio.h"

#define PWM_COM_OFF 0
#define PWM_COM_TOGGLE 1
#define PWM_COM_CLEAR 2
#define PWM_COM_SET 3

#define PWM_MAX 255

typedef struct {
	//const timer_s * timer;
	uint8_t * ocr;
} pwm_s;

extern pwm_s PWM0;
extern pwm_s PWM1;
extern pwm_s PWM2;

#ifdef __cplusplus
extern "C" {
#endif

void pwm_init();

// void pwm_stop(pwm_s*);
// void pwm_start(pwm_s*);

void pwm_set_duty(pwm_s*, uint8_t);
uint8_t pwm_get_duty(pwm_s*);

// All functions are inlined for maximum performance

extern inline
void pwm_set_duty(pwm_s* p, uint8_t duty){
	*p->ocr = duty;
}
extern inline
uint8_t pwm_get_duty(pwm_s* p){
	// Get timer compare register
	return *p->ocr;
}

#ifdef __cplusplus
}
#endif

#endif // PWM_H