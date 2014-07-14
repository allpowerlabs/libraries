#include <stdio.h>
#include <list.h>

#define NODECOUNT 5

lnode nodes[NODECOUNT + 1];
list doink;
unsigned rlimit = 0;	// Recursion limit

int foobz (lnode * n) {
	rlimit++;
	printf("\n\t\t");
	if (rlimit > RLIMIT) {printf("\n!!! Recursion limit reached !!!\n"); return 1;}
	printf("%8p<-[%8p]->%-8p ", n->prev, n, n->next);
	printf("\t");
	if (n->prev && n->prev->next != n) printf("!<");
	if (n->next && n->next->prev != n) printf(">!");
	printf("\t");
	if (n == doink.head) printf("H ");
	if (n == doink.tail) printf("T ");
	return 0;
}

int checklist(list * l, unsigned len, unsigned max) {
	lnode * x;
	unsigned refcount, fail;
	
	printf("Checking head node... ");
	if (l->head && l->head->prev) {
		printf("FAILED\n\tHead node does not terminate list!\n");
		fail++;
	} else printf("OKAY\n");
	
	printf("Checking tail node... ");
	if (l->tail && l->tail->next) {
		printf("FAILED\n\tTail node does not terminate list!\n");
		fail++;
	} else printf("OKAY\n");
	
	printf("Scanning list forward... ");
	x = l->head;
	refcount = 0;
	while (x) {
		refcount++;
		if (refcount > max) {
			printf("FAILED\n\tToo many nodes!\n");
			fail++;
			break;
		}
		if (!node_checkref(x->prev, x)) {
			printf("FAILED\n\tPrevious node does not reference this node!\n");
			fail++;
		}
		if (!node_checkref(x, x->next)) {
			printf("FAILED\n\tNext node does not reference this node!\n");
			fail++;
		}
		x = x->next;
	}
	printf("\n");
	printf("Checking reference count... ");
	if (refcount > len) {
		printf("FAILED\n\tList too long!\n");
		fail++;
	}
	if (refcount < len) {
		printf("FAILED\n\tList too short\n");
		fail++;
	}
	if (refcount == len) {
		printf("OKAY\n");
	}
	printf("Scanning list backward... ");
	x = l->tail;
	refcount = 0;
	while (x) {
		refcount++;
		if (refcount > max) {
			printf("FAILED\n\tToo many nodes!\n");
			fail++;
			break;
		}
		if (!node_checkref(x->prev, x)) {
			printf("FAILED\n\tPrevious node does not reference this node!\n");
			fail++;
		}
		if (!node_checkref(x, x->next)) {
			printf("FAILED\n\tNext node does not reference this node!\n");
			fail++;
		}
		x = x->prev;
	}
	printf("\n");
	printf("Checking reference count... ");
	if (refcount > len) {
		printf("FAILED\n\tList too long!\n");
		fail++;
	}
	if (refcount < len) {
		printf("FAILED\n\tList too short\n");
		fail++;
	}
	if (refcount == len) {
		printf("OKAY\n");
	}
	printf("\n");
	return fail;
}

void showlist() {
		rlimit = 0;
		printf("%02d ", doink.len);
		printf("%p", doink.head);
		if (doink.head == doink.tail) printf("==");
		else printf("..");
		printf("%p", doink.tail);
		if (!(doink.head || doink.tail)) printf("[EMPTY]");
		else list_scan(&doink, foobz);
		puts("\n");
}

int main(int argc, char * argv[]) {
	int i;
	// --------------------------------
	puts("------------------ Clearing empty list...");
	list_clear(&doink);
	showlist();
	//checklist(&doink, 0, 100);
	// --------------------------------
	puts("------------------ Appending to tail...");
	for (i=0; i < NODECOUNT; i++) {
		printf("Node %d (%p)\n", i, &nodes[i]);
		list_append(&doink, &nodes[i]);
		showlist();
	}
	//checklist(&doink, NODECOUNT, 100);
	// --------------------------------
	puts("------------------ Removing from tail...");
	for (i=NODECOUNT-1; i > -1; i--) {
		printf("Node %d (%p)\n", i, &nodes[i]);
		list_remove(&doink, doink.tail);
		showlist();
	}
	// --------------------------------
	puts("------------------ Prepending to head...");
	list_clear(&doink);
	showlist();
	for (i=0; i < NODECOUNT; i++) {
		printf("Node %d (%p)\n", i, &nodes[i]);
		list_prepend(&doink, &nodes[i]);
		showlist();
	}	
	// --------------------------------
	puts("------------------ Removing from head...");
	list_clear(&doink);
	for (i=0; i < NODECOUNT; i++) { list_append(&doink, &nodes[i]); }
	showlist();
	for (i=0; i < NODECOUNT; i++) {
		printf("Node %d (%p)\n", i, &nodes[i]);
		list_remove(&doink, doink.head);
		showlist();
	}
	// --------------------------------
	list_clear(&doink);
	for (i=0; i < NODECOUNT; i++) { list_append(&doink, &nodes[i]); }
	puts("------------------ Removing from middle...");
	showlist();
	for (i=1; i < NODECOUNT-1; i++) {
		printf("Node %d (%p)\n", i, &nodes[i]);
		list_remove(&doink, &nodes[i]);
		showlist();
	}
	// --------------------------------
	puts("------------------ Appending dirty nodes to empty list...");
	list_clear(&doink);
	for (i=0; i < NODECOUNT; i++) { list_append(&doink, &nodes[i]); }
	doink.head = 0; doink.tail = 0; doink.len = 0;
	showlist();
	for (i=0; i < NODECOUNT; i++) {
		printf("Node %d (%p)\n", i, &nodes[i]);
		list_append(&doink, &nodes[i]);
		showlist();
	}
	// --------------------------------
	puts("------------------ Adding duplicates, test 1...");
	for (i=0; i < NODECOUNT; i++) { list_append(&doink, &nodes[i]); }	// Reload the list
	showlist();
	for (i=NODECOUNT-1; i > -1; i--) {
		printf("Node %d (%p)\n", i, &nodes[i]);
		list_append(&doink, &nodes[i]);
		showlist();
	}
	checklist(&doink, 0, 100);
	// --------------------------------
	list_clear(&doink);
	puts("------------------ Adding duplicates, test 2...");
	showlist();
	for (i=0; i < NODECOUNT; i++) {
		printf("Node %d (%p)\n", 0, &nodes[0]);
		list_append(&doink, &nodes[0]);
		showlist();
	}
	checklist(&doink, 0, 100);
	// --------------------------------
	list_clear(&doink);
	for (i=0; i < NODECOUNT; i++) { list_append(&doink, &nodes[i]); }
	puts("------------------ Removing bad node, test 1...");
	showlist();
	nodes[NODECOUNT].prev = &nodes[NODECOUNT-1]; nodes[NODECOUNT].next = &nodes[0];
	printf("Bad Node (%p<-[%p]->%p) \n", nodes[NODECOUNT].prev, &nodes[NODECOUNT], nodes[NODECOUNT].next);
	list_remove(&doink, &nodes[4]);
	showlist();
	checklist(&doink, 0, 100);
	// --------------------------------
	list_clear(&doink);
	for (i=0; i < NODECOUNT; i++) { list_append(&doink, &nodes[i]); }
	puts("------------------ Removing bad node, test 2...");
	showlist();
	nodes[NODECOUNT].prev = &nodes[0]; nodes[NODECOUNT].next = &nodes[NODECOUNT-1];
	printf("Bad Node (%p<-[%p]->%p) \n", nodes[NODECOUNT].prev, &nodes[NODECOUNT], nodes[NODECOUNT].next);
	list_remove(&doink, &nodes[4]);
	showlist();
	checklist(&doink, 0, 100);
/*	// --------------------------------
	// Clear the list
	while (list_remove(&doink, doink.tail));
	// Reload the list
	for (i=0; i < 4; i++) { list_append(&doink, &nodes[i]); }
	puts("\nRemoving bad node, test 2...");
	showlist();
	nodes[4].prev = &nodes[3]; nodes[4].next = &nodes[0];
	printf("Node 4 (%p<-[%p]->%p) \n", nodes[4].prev, &nodes[4], nodes[4].next);
	list_remove(&doink, &nodes[4]);
	showlist();
*/

	return 0;
}
