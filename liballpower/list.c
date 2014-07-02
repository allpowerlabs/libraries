
#ifndef ARDUINO
#include "list.h"
#endif

lnode * list_insert(lnode * n, lnode * m) {
	if (!n) return 0;
	*m = *n;
	*n = m;
	return *m;
}
lnode * list_scan(lnode * n, lfunc f) {
	while (n) {
		if (f(n)) return n;
		n = *n;
	}
	return 0;
}

lnode * list_remove(lnode * list, lnode * n) {
}

lnode * list_append(lnode * list, lnode * n) {	
}
