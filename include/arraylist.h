#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>
#include <stdbool.h>

struct arraylist_t{
    void** list;   // The array of pointers to data
    size_t length; // The number of spaces in the list that have been filled
    size_t size;   // The number of allocated spaces in the list
};
typedef struct arraylist_t arraylist_t;

bool arraylist_init(arraylist_t*);
void arraylist_free(arraylist_t*);
bool arraylist_resize(arraylist_t*, size_t);
bool arraylist_reserve(arraylist_t*, size_t);

bool arraylist_append(arraylist_t*, void*);
bool arraylist_add(arraylist_t*, size_t, void*);
void* arraylist_remove(arraylist_t*, size_t);

size_t arraylist_length(arraylist_t*);
void** arraylist_toarray(arraylist_t*);
void* arraylist_get(arraylist_t*, size_t);
ptrdiff_t arraylist_indexof(arraylist_t*, void*, int (*cmp) (void*, void*));

#endif