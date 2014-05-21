#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "vnh_bridge.h"
#include "adc.h"
#include "intmath.h"

const char PROGMEM vnh_stdby_str[] = "STDBY";
const char PROGMEM vnh_fwd_str[] = "FWD";
const char PROGMEM vnh_rev_str[] = "REV";
const char PROGMEM vnh_brk_str[] = "BRAKE";

const char * vnh_modes[] = {
	vnh_stdby_str,
	vnh_fwd_str,
	vnh_rev_str,
	vnh_brk_str
};

void vnh_disable(vnh_s* v){
	// Set enable pins as outputs
	gpio_set_ddr(v->ena);
	gpio_set_ddr(v->enb);
	// Disable outputs
	gpio_clr_pin(v->ena);
	gpio_clr_pin(v->enb);
}

void vnh_enable(vnh_s* v){
	// Set enable pins as inputs
	gpio_clr_ddr(v->ena);
	gpio_clr_ddr(v->enb);
	// Enable outputs
	gpio_set_pin(v->ena);
	gpio_set_pin(v->enb);
}

void vnh_reset(vnh_s* v){
	// Set pins for switches as outputs
	gpio_set_ddr(v->mota);
	gpio_set_ddr(v->motb);
	// Disable outputs
	vnh_disable(v);
	// Toggle motor outputs to clear any faults
	gpio_set_pin(v->mota);
	gpio_set_pin(v->motb);
	gpio_clr_pin(v->mota);
	gpio_clr_pin(v->motb);
	// Set mode
	v->mode = VNH_STANDBY;
}

void vnh_standby(vnh_s* v){
	vnh_disable(v);
	gpio_clr_pin(v->mota);
	gpio_clr_pin(v->motb);
	// Set mode
	v->mode = VNH_STANDBY;
}

void vnh_forward(vnh_s* v){
	vnh_disable(v);			// Disable outputs
	// A=hi, B=lo
	gpio_set_pin(v->mota);
	gpio_clr_pin(v->motb);
	vnh_enable(v);			// Enable outputs
	// Set status
	v->mode = VNH_FORWARD;
}
	
void vnh_reverse(vnh_s* v){
	vnh_disable(v);			// Disable outputs
	// A=lo, B=hi
	gpio_clr_pin(v->mota);
	gpio_set_pin(v->motb);
	vnh_enable(v);			// Enable outputs
	// Set status
	v->mode = VNH_REVERSE;
}

void vnh_brake(vnh_s* v){
	vnh_disable(v);			// Disable outputs
	// A=lo, B=lo
	gpio_set_pin(v->mota);
	gpio_set_pin(v->motb);
	vnh_enable(v);			// Enable outputs
	v->mode = VNH_BRAKE;
}

uint8_t vnh_get_mode(vnh_s *v){
	return v->mode;
}
uint8_t vnh_get_fault(vnh_s* v) {
	return gpio_get_pin(v->ena) | gpio_get_pin(v->enb);
}
