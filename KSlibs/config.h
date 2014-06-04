// config.h

typedef struct confval_s{
	unsigned long hash;
	unsigned long value;
	const char * label;
	void (*validate)(struct confval_s*);
} confval_s;