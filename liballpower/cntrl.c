#include <cntrl.h>

long compute(struct cntrl *c, long input) {
	long err;
	long P;
	long I;
	long output;
	
	err = c->setpoint - input;	// Calculate the error
	c->Ierr += err;					// Integrate the error
	// Integral saturation to prevent windup
	if (c->Ierr > c->Imax) c->Ierr = c->Imax;
	if (c->Ierr < c->Imin) c->Ierr = c->Imin;
	// Calculate and return
	P = (c->Pgain * err);
	I = (c->Igain * c->Ierr);
	output = c->bias + ((P + I) / c->atten);
	if (output > c->max) output = c->max;
	if (output < c->min) output = c->min;
	return output;
}