typedef struct {
	vnh_s * hbridge;
	pwm_s * pwm;
	adc_s * adc;
	uint16_t low_current;
	uint16_t high_current;
	uint16_t limit_current;
	uint8_t gain;
} motor_s;