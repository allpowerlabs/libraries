// list.h

typedef void * lnode;

typedef int (* lfunc)(lnode *);

lnode * list_insert(lnode *, lnode *);  
lnode * list_scan(lnode *, lfunc);
lnode * list_remove(lnode *, lnode *);
lnode * list_append(lnode *, lnode *);
