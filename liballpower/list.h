// list.h
#ifndef LIST_H
#define LIST_H

#define RLIMIT 500
#define offsetof(TYPE, MEMBER) ( \
	(size_t) &((TYPE *) 0)->MEMBER \
)
#define list_node(NODE_PTR, TYPE, MEMBER) ( \
	(TYPE *) ((unsigned char *) NODE_PTR - offsetof(TYPE, MEMBER)) \
)

typedef struct lnode {
	struct lnode * prev;
	struct lnode * next;
} lnode;

typedef struct list {
	struct lnode * head;
	struct lnode * tail;
	unsigned len;
} list;

typedef int (* lfunc)(lnode *);

#ifdef __cplusplus
extern "C" {
#endif

int node_checkref(lnode *, lnode *);

lnode * list_insert_after(list *, lnode *, lnode *);  
lnode * list_scan(list *, lfunc);
lnode * list_append(list *, lnode *);
lnode * list_prepend(list *, lnode *);
lnode * list_remove(list *, lnode *);

lnode * list_first(list *);
lnode * list_last(list *);

#ifdef __cplusplus
}
#endif

#endif // LIST_H