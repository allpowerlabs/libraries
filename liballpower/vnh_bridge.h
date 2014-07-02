/*
  Driver API for VNH2SP30
*/

#include <avr/pgmspace.h>

#include "gpio.h"
#include "intmath.h"
#include "timer.h"
#include "pwm.h"

#define VNH_ADC_UNIT (37538)		// Unit for ADC to uA conversion

#define VNH_STANDBY 0
#define VNH_FORWARD 1
#define VNH_REVERSE 2
#define VNH_BRAKE 3

typedef struct {
	uint8_t mode;			// 0=STDBY, 1=FWD, 2=REV, 3=BRAKE
	gpio_s mota;
	gpio_s motb;
	gpio_s ena;
	gpio_s enb;
} vnh_s;

extern const char * PROGMEM vnh_modes[];

#ifdef __cplusplus
extern "C" {
#endif

void vnh_reset(vnh_s*);		// Reset, clear fault
void vnh_forward(vnh_s*);	// A=hi, B=lo
void vnh_reverse(vnh_s*);	// A=lo, B=hi
void vnh_brake(vnh_s*);		// A=lo, B=lo
void vnh_standby(vnh_s*);	// Disable A, B

uint8_t vnh_get_mode(vnh_s*);
uint8_t vnh_get_fault(vnh_s*);

#ifdef __cplusplus
}
#endif