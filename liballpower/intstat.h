typedef struct {
	unsigned int avg;
	unsigned int head;
	unsigned long accum;
	unsigned int size;
	unsigned int *samples;
} sbuf_s;

#ifdef __cplusplus
extern "C" {
#endif

unsigned int average (sbuf_s *);
unsigned int sample (sbuf_s *, unsigned int);

#ifdef __cplusplus
}
#endif