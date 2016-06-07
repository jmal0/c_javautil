#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct arraylist_t arraylist_t;
struct arraylist_t{
    void** list;   // The array of pointers to data
    size_t length; // The number of spaces in the list that have been filled
    size_t size;   // The number of allocated spaces in the list
};

bool arraylist_init(arraylist_t*);
void arraylist_free(arraylist_t*);
bool arraylist_resize(arraylist_t*, const size_t);
bool arraylist_reserve(arraylist_t*, const size_t);

bool arraylist_append(arraylist_t*, void*);
bool arraylist_add(arraylist_t*, const size_t, void*);
void* arraylist_remove(arraylist_t*, const size_t);

size_t arraylist_length(const arraylist_t*);
void** arraylist_toarray(const arraylist_t*);
void* arraylist_get(const arraylist_t*, const size_t);
ptrdiff_t arraylist_indexof(const arraylist_t*, const void*, 
                            int (*cmp) (const void*, const void*));

#endif
