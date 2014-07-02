#ifndef PWM_H
#define PWM_H

#include <stdint.h>
//#include "intmath.h"
//#include "timer.h"
//#include "gpio.h"

// #define PWM_COM_OFF 0
// #define PWM_COM_TOGGLE 1
// #define PWM_COM_CLEAR 2
// #define PWM_COM_SET 3

#define PWM_MAX 255

//#define PWM0 PWM0
#define PWM1 PWM1
#define PWM2 PWM2
//#define PWM3 PWM3
#define PWM4 PWM4
//#define PWM5 PWM5

typedef struct {
	//const timer_s * timer;
	uint8_t * ocr;
} pwm_s;

#ifdef PWM0
extern pwm_s PWM0;
#endif
#ifdef PWM1
extern pwm_s PWM1;
#endif
#ifdef PWM2
extern pwm_s PWM2;
#endif
#ifdef PWM3
extern pwm_s PWM3;
#endif
#ifdef PWM4
extern pwm_s PWM4;
#endif
#ifdef PWM5
extern pwm_s PWM5;
#endif

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