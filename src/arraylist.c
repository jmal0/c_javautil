/*
 c dynamic array structure
*/
#include "../include/arraylist.h"

const size_t arraylist_initsize = 8;
const size_t arraylist_resize_factor = 2;

/**
 * Initialize a pointer to an arraylist to a default size of 8. Returns t/f
 * depending on the successful allocation of the list pointer
 */
bool arraylist_init(arraylist_t* lst){
    lst->size = arraylist_initsize;
    lst->length = 0;
    lst->list = (void**) malloc(arraylist_initsize*sizeof(void*));
    return lst->list != NULL;
}

/**
 * Frees the memory allocated fir an arraylist pointer. Should be called when 
 * the arraylist is no longer needed and before freeing the pointer itself
 */
void arraylist_free(arraylist_t* lst){
    if (lst->list){
        free(lst->list);
    }
}

/**
 * Resizes the list to the specified size. Returns t/f depending on the
 * successful allocation of the requested amount of memory
 */
bool arraylist_resize(arraylist_t* lst, const size_t size){
    lst->size = size;
    lst->list = (void**) realloc(lst->list, size*sizeof(void*));
    return lst->list != NULL;
}

/**
 * Ensure that sufficient space has been allocated to the list to store the
 * specified number of items. Will resize the array by default factor of 2 if
 * there is insufficient space. If there is sufficient space, nothing is 
 * changed. Returns t/f depending on the successful allocation of the necessary 
 * amount of memory
 */
bool arraylist_reserve(arraylist_t* lst, const size_t items){
    if (lst->size < items){
        return arraylist_resize(lst, arraylist_resize_factor*lst->size);
    }
    return true;
}

/**
 * Append the given item to the arraylist. Returns t/f on the successful append
 * of the data and possible reallocation of memory
 */
bool arraylist_append(arraylist_t* lst, void* data){
    bool success = arraylist_reserve(lst, lst->length + 1);
    if(success){
        lst->list[lst->length] = data;
        lst->length++;
    }
    return success;
}

/**
 * Add the given item to the arraylist at the specified index. All later items 
 * will be moved to the next index. Returns t/f on the successful addition of
 * the data and possible reallocation of memory
 */
bool arraylist_add(arraylist_t* lst, const size_t ind, void* data){
    bool success = arraylist_reserve(lst, lst->length + 1);
    if(success){
        size_t i;
        for(i = lst->length; i > ind; i--){
            lst->list[i] = lst->list[i-1];
        }
        lst->list[i] = data;
        lst->length++;
    }
    return success;
}

/**
 * Removes the data at the specified index from the list and returns the removed
 * data pointer
 */
void* arraylist_remove(arraylist_t* lst, const size_t ind){
    void* data = lst->list[ind];
    size_t i;
    for(i = ind; i < lst->length - 1; i++){
        lst->list[i] = lst->list[i + 1];
    }
    return data;
}

/**
 * Returns the number of items in the arraylist
 */
size_t arraylist_length(arraylist_t* lst){
    return lst->length;
}

/**
 * Returns a pointer to the dynamic array contained in this arraylist
 */
void** arraylist_toarray(arraylist_t* lst){
    return lst->list;
}

/**
 * Returns the item at the specified index of the arraylist
 */
void* arraylist_get(arraylist_t* lst, const size_t ind){
    return lst->list[ind];
}

/**
 * Searches the arraylist for the specified item using the given comparator
 * function to check for equality. Returns the index at which the item was found
 * or -1 if it was not found
 */
ptrdiff_t arraylist_indexof(arraylist_t* lst, const void* data, 
                            int (*cmp) (const void*, const void*)){
    size_t i = 0;
    while(i < lst->length && (*cmp)(data, lst->list[i]) != 0){
        i++;
    }
    return i < lst->length ? i : -1;
}
