#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static inline const size_t _PQ_PARENT(size_t ind){
    return (ind-1)/2;
}

static inline const size_t _PQ_LEFT(size_t ind){
    return 2*ind+1;
}

static inline const size_t _PQ_RIGHT(size_t ind){
    return 2*ind+2;
}

typedef struct priorityqueue_t priorityqueue_t;
struct priorityqueue_t{
    void** data;   // Array of data pointers
    size_t length; // # of elements in heap array
    size_t size;   // Allocated space in heap array
    int (*cmp)(const void*, const void*); // Comparator for queue items
};

bool priorityqueue_init(priorityqueue_t*, int (*)(const void*, const void*));
void priorityqueue_free(priorityqueue_t*);
bool priorityqueue_reserve(priorityqueue_t*, size_t size);

bool priorityqueue_add(priorityqueue_t*, void*);
bool priorityqueue_addall(priorityqueue_t*, void**, const size_t len);
bool priorityqueue_remove(priorityqueue_t*, const void*);
void priorityqueue_clear(priorityqueue_t*);
void* priorityqueue_poll(priorityqueue_t*);

bool priorityqueue_contains(const priorityqueue_t*, const void*);
size_t priorityqueue_size(const priorityqueue_t*);
void** priorityqueue_toarray(const priorityqueue_t*);
void* priorityqueue_peek(const priorityqueue_t*);

bool validate_heap(const priorityqueue_t*);

#endif
