/*
  Driver API for VNH2SP30
*/

#include "gpio.h"
#include "intmath.h"

#define VNH_ADC_UNIT (37538)		// Unit for ADC to mA conversion
#define VNH_SAMPLES (64)			// Number of samples for AVG function
#define VNH_DIVISOR (6)				// Bit shift divisor x, y / 2^x
#define VNH_MOD_MAX (100)			// PWM counter maximum, 100 for duty in %
#define VNH_FAULT_MASK (0x4C)

#define VNH_STANDBY 0
#define VNH_FORWARD 1
#define VNH_REVERSE 2
#define VNH_BRAKE 3
#define VNH_LIMIT 1

#define VNH_PWM_NONE 0
#define VNH_PWM_FIXED 1
#define VNH_PWM_SOFT 2

typedef void (*vnh_hook_f)(void);

typedef struct {
	uint8_t mode:2;			// 0=STDBY, 1=FWD, 2=REV, 3=BRK
	uint8_t fault_A:1;		// Fault detected on channel A
	uint8_t fault_B:1;		// Fault detected on channel B
	uint8_t limit:1;		// 1 if over-current threshold reached
} vnh_status_s;

typedef struct {
	unsigned int avg;
	unsigned int head;
	unsigned long accum;
	unsigned int samples[VNH_SAMPLES];
} vnh_sbuf_s;

typedef struct {
	uint8_t	mode;			// PWM mode: none, fixed, or soft start
	uint8_t target;			// Target PWM duty
//	uint8_t duty;			// Current duty
//	uint8_t count;			// Cycle counter
	uint8_t ramp;			// Ramp rate
} vnh_mod_s;

typedef struct {
	vnh_status_s status;
	gpio_s mota;
	gpio_s motb;
	gpio_s ena;
	gpio_s enb;
	gpio_s pwm;
	unsigned int adc;		// ADC channel for current sense
	unsigned int climit;	// Current limit, in ADC units
	unsigned int chyst;		// Current limit hysteresis
	vnh_mod_s mod;			// Modulation
	vnh_sbuf_s avg;			// Averaging sample buffer
	vnh_hook_f pwm_start;
	vnh_hook_f pwm_stop;
} vnh_s;

#ifdef __cplusplus
extern "C" {
#endif

void vnh_reset(vnh_s*);		// Reset, clear fault
void vnh_forward(vnh_s*);	// A=hi, B=lo
void vnh_reverse(vnh_s*);	// A=lo, B=hi
void vnh_brake(vnh_s*);		// A=lo, B=lo
void vnh_standby(vnh_s*);	// Disable A, B

void vnh_adc_tick(vnh_s* v);

unsigned int vnh_get_current(vnh_s*); // Returns average current
vnh_status_s vnh_get_status(vnh_s*);
uint8_t vnh_get_fault(vnh_s*);

void vnh_avg_reset(vnh_s*);

void vnh_pwm_reset(vnh_s*);
void vnh_pwm_stop(vnh_s* v);
void vnh_pwm_start(vnh_s* v);

void vnh_set_duty(vnh_s* v, uint16_t d);
uint16_t vnh_get_duty(vnh_s* v);

// PWM ISRs.  These are inlined for maximum performance


extern inline
void vnh_pwm_cmp(vnh_s* v){
	gpio_clr_pin(v->pwm);
}
extern inline
void vnh_pwm_ovf(vnh_s* v){
	gpio_set_pin(v->pwm);
	
	if (v->status.limit) {
		// Ramp down during current limit
		vnh_set_duty(v, u_sublim(vnh_get_duty(v), v->mod.ramp, 0));
	}
	else {
		// Ramp up when below target
		vnh_set_duty(v, u_addlim(vnh_get_duty(v), v->mod.ramp, v->mod.target));
	}
}
#ifdef __cplusplus
}
#endif