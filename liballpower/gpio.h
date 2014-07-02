#ifndef GPIO_H
#define GPIO_H
typedef struct gpio {
	volatile uint8_t *port;
	unsigned char pin;
} gpio_s;

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif

// Set bit in DDR
inline
void gpio_set_ddr(gpio_s p){*(p.port - 1) |= _BV(p.pin);}
// Clear bit in DDR
inline
void gpio_clr_ddr(gpio_s p){*(p.port - 1) &= 0xFF & ~_BV(p.pin);}
// Set pin in PORT
inline
void gpio_set_pin(gpio_s p){*p.port |= _BV(p.pin);}
// Clear pin in PORT
inline
void gpio_clr_pin(gpio_s p){*p.port &= 0xFF & ~_BV(p.pin);}
// Get PIN value
inline
unsigned char gpio_get_pin(gpio_s p){return *(p.port - 2) & _BV(p.pin);}
// Toggle pin
//void gpio_toggle_pin(gpio_s p){*p.port &= 0xFF & ~_BV(p.pin);}
#ifdef __cplusplus
}
#endif

#endif // GPIO_H