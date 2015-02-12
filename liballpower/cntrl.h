#ifndef CNTRL_H
#define CNTRL_H

struct cntrl {
	long setpoint;
	long bias;	// Ouput bias, not scaled
	long Pgain;	// Proportional gain
	long Igain;	// Integral gain
	long Dgain;
	long Ierr;	// Accumulated error (integral)
	long Imin;	// Integral min
	long Imax;	// Integral max
	long min;	// Min output value
	long max;	// Max output value
	long atten;	// Attenuation coefficient
};

#ifdef __cplusplus
extern "C" {
#endif

long compute(struct cntrl *, long input);

#ifdef __cplusplus
}
#endif

#endif // CNTRL_H