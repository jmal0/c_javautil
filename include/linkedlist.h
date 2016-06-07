#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct _llnode_t _llnode_t;
struct _llnode_t{
    _llnode_t* next; // Next element in list
    void* data;      // Pointer to the data in this node
};

typedef struct linkedlist_t linkedlist_t;
struct linkedlist_t{
    size_t length;    // Number of elements in list, stored for convenience
    _llnode_t* start; // Pointer to the first node in the list
};

void linkedlist_init(linkedlist_t*);
void linkedlist_free(linkedlist_t*);

bool linkedlist_append(linkedlist_t*, void*);
bool linkedlist_add(linkedlist_t*, const size_t, void*);
void* linkedlist_remove(linkedlist_t*, const size_t);

size_t linkedlist_length(const linkedlist_t*);
void** linkedlist_toarray(const linkedlist_t*);
void* linkedlist_get(const linkedlist_t*, const size_t);
ptrdiff_t linkedlist_indexof(const linkedlist_t*, const void*, 
                            int (*cmp) (const void*, const void*));

#endif
