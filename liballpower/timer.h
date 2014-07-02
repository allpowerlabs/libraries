#ifndef TIMER_H
#define TIMER_H

// Note: it would be really great to use ATOMIC_BLOCK to turn off interrupts
// around these register accesses, but unfortunately we'd have to switch
// to compiling this with C99, which isn't supported by the Arduino IDE.
//#include <util/atomic.h>

typedef struct timer_s {
	unsigned long count;
	unsigned direction: 1;
	struct timer_s * next;
} timer_s;

#ifdef __cplusplus
extern "C" {
#endif

void timer_init();
void timer_start(timer_s *);
void timer_stop(timer_s *);
void timer_set(timer_s *, unsigned long);
unsigned long timer_read(timer_s *);

#ifdef __cplusplus
}
#endif

#endif	// TIMER_H