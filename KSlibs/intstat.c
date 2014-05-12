// intstat.c - integer statistical analysis functions
#include "intstat.h"

unsigned int average (sbuf_s * buf) {
	buf->avg = (buf->accum / buf->size);		// Divide the accumulator
	return buf->avg;
}

unsigned int sample (sbuf_s * buf, unsigned int s) {
	buf->accum -= buf->samples[buf->head]; 				// Subtract oldest sample
	buf->accum += s;									// Add new sample
	buf->samples[buf->head] = s;						// Store new sample
	buf->head++;										// Advance head
	if (buf->head == buf->size) buf->head = 0;			// Roll over if needed
/* 
	if (buf->head < (buf->size - 1)) {
		buf->accum -= buf->samples[++buf->head];			// Subtract sample at tail and advance head
		buf->samples[buf->head] = s;						// Overwrite old sample
		buf->accum += buf->samples[buf->head];				// Add the latest sample
	}
	else {
		// Roll over
		buf->accum -= buf->samples[0];				// Subtract sample at tail and advance head
		buf->samples[0] = s;						// Overwrite old sample
		buf->accum += buf->samples[0];				// Add the latest sample
		buf->head = 0;
	}
 */
}

void sbuf_reset(sbuf_s* buf){
	int x;
	// Clear sample buffer
	for (x=0; x < buf->size; x++) {
		buf->samples[x] = 0;
	}
	buf->head = 0;
	buf->accum = 0;
}