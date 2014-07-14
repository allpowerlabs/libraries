#define _LIST_C
#include "list.h"

/*
	node insertion
n and m are nodes, with m being inserted between n and the next node.
	Before insertion:
		n->o
	After insertion:
		n->m->o

if n happens to be the end of the list it should point to NULL.
	n->NULL
When m is inserted it becomes the end of the list
	n->m->NULL


Linking a node:
	1. Make sure A and B aren't NULL, or we break the list
		A != 0 && B != 0
	2. Link B to A and C
		A<->C
		^-B-^
	3. Link A and C to B
		A<->B<->C

Unlinking a node
	Check references A<->C and C<->B
		A-->C<--B   A<--C-->B
	Link A to B and B to A
		A-->B   A<--B   A<->B
	Unlink C
		0<--C-->0
*/

int list_match(lnode * n) {
return 0;
}

int node_checkref(lnode * a, lnode * b) {
	if ((!a || (a && a->next == b)) && (!b || (b && b->prev == a))) return 1;
	else return 0;	
}

void node_link(lnode * a, lnode * b) {
	if (a) a->next = b;
	if (b) b->prev = a;
}

void node_insert_before(lnode * a, lnode * b) {
	lnode * c = 0;
	if (a) c = a->prev;
	node_link(c, b);
	node_link(b, a);
}

void node_insert_after(lnode * a, lnode * b) {
	lnode * c = 0;
	if (a) c = a->next;
	node_link(a, b);
	node_link(b, c);
}

void node_unlink(lnode * n) {
	if (n) {
		//~ // Have to double-check that the nodes we point to point back to us...
		//~ if (node_checkref(n->prev, n) && node_checkref(n, n->next)) {
			
		//~ }
		node_link(n->prev, n->next);
		n->prev = 0;
		n->next = 0;
	}
}


lnode * list_first(list * l) {
	return l->head;
}

lnode * list_last(list * l) {
	return l->tail;
}

lnode * list_insert_before(list * l, lnode * n, lnode * m) {
	if (!(l && n && m)) return 0;	// Check for null pointers
	node_insert_before(n, m);
	if (l->head == n) l->head = m;
	return m;
}

lnode * list_insert_after(list * l, lnode * n, lnode * m) {	
	if (!(l && n && m)) return 0;	// Check for null pointers
	node_insert_after(n, m);
	if (l->tail == n) l->tail = m;
	return m;
}

lnode * list_scan(list * l, lfunc f) {
	unsigned rlimit = RLIMIT;
	lnode * c = l->head;
	while (c) {
		rlimit--;  
		if (!rlimit) return 0;
		if (f(c)) return c;
		c = c->next;
	}
	return 0;
}

lnode * list_append(list * l, lnode * a) {
	if (!(l && a)) return 0;	// Check for null pointers
	list_remove(l, a);		// Remove the node from the list to make sure it doesn't mess things up
	if (l->head) {
		list_insert_after(l, l->tail, a);
	}
	else {				// Null list
		l->head = a;
		a->prev = 0;
		a->next = 0;
		l->tail = a;
	}
	l->len++;
	return a;
}

lnode * list_prepend(list * l, lnode * a) {
	if (!(l && a)) return 0;	// Check for null pointers
	if (l->head) {
		list_insert_before(l, l->head, a);
	}
	else {				// Null list
		l->head = a;
		a->prev = 0;
		a->next = 0;
		l->tail = a;
	}
	l->len++;
	return a;
}

lnode * list_remove(list * l, lnode * r) {
	if (!(l && r)) return 0;	// Check for null pointers
	if (l->head == 0) return 0;	// Null list, nothing to do
	if (!node_checkref(r->prev, r) || !node_checkref(r, r->next)) return 0;	// Make sure r is properly linked
	if (r == l->head) l->head = r->next;
	if (r == l->tail) l->tail = r->prev;
	node_unlink(r);
	l->len--;
	return r;
}

void list_clear(list * l) {
	unsigned rlimit = RLIMIT;
	while (list_remove(l, l->tail)) {
		rlimit--;
		if (!rlimit) return;
	}
}