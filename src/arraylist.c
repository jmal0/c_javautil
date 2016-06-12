/*
 c dynamic array structure
*/
#include "arraylist.h"

const size_t arraylist_initsize = 8;
const size_t arraylist_resize_factor = 2;

/**
 * Initialize a pointer to an arraylist to a default size of 8. 
 * @param lst  The pointer to intialize as an arraylist
 * @return  t/f depending on the successful allocation of the list
 */
bool arraylist_init(arraylist_t* lst){
    lst->size = arraylist_initsize;
    lst->length = 0;
    lst->list = (void**) malloc(arraylist_initsize*sizeof(void*));
    return lst->list != NULL;
}

/**
 * Frees the memory allocated for an arraylist pointer
 * <p>
 * This function should be called when the arraylist is no longer needed and 
 * before freeing the pointer itself
 * @param lst  The arraylist to free
 */
void arraylist_free(arraylist_t* lst){
    if (lst->list){
        free(lst->list);
    }
}

/**
 * Resizes the list to the specified size
 * @param lst   The arraylist to resize
 * @param size  The number of elements to reserve room for
 * @return  t/f depending on the successful allocation of the requested memory
 */
bool arraylist_resize(arraylist_t* lst, const size_t size){
    lst->size = size;
    lst->list = (void**) realloc(lst->list, size*sizeof(void*));
    return lst->list != NULL;
}

/**
 * Ensure that sufficient space has been allocated to the list to store the
 * specified number of items.
 * <p>
 * Will resize the array by a factor of 2 if there is insufficient space. If 
 * there is sufficient space, nothing is changed
 * @param lst   The arraylist to resize
 * @param newsize  The number of elements to reserve memory for
 * @return  t/f depending on the successful allocation of memory
 */
bool arraylist_reserve(arraylist_t* lst, const size_t newsize){
    if (lst->size < newsize){
        size_t size = lst->size;
        while(size < newsize){
            size *= arraylist_resize_factor;
        }
        return arraylist_resize(lst, size);
    }
    return true;
}

/**
 * Append the given item to the arraylist
 * @param lst   The arraylist to append to
 * @param data  The data to add
 * @return  t/f depending on the successful addition of the item to the array
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
 * Add the given item to the arraylist at the specified index
 * @param lst   The arraylist to add to
 * @param ind   The index at which to add the data
 * @param data  The data to add
 * @return  t/f depending on the successful addition of the item to the array
 */
bool arraylist_add(arraylist_t* lst, const size_t ind, void* data){
    bool success = arraylist_reserve(lst, lst->length + 1);
    if(success){
        size_t i;
        for(i = lst->length; i > ind; i--){
            lst->list[i] = lst->list[i - 1];
        }
        lst->list[i] = data;
        lst->length++;
    }
    return success;
}

/**
 * Add all items in an array to the list at the specified index
 * @param lst  The arraylist to add to
 * @param ind  The index at which to add the fist element of the array
 * @param len  The length of the array of data to add
 * @param ary  The array of pointers to add to the list
 * @return  t/f depending on the successful addition of the items to the array
 */
bool arraylist_addall(arraylist_t* lst, const size_t ind, const size_t len, 
                      void** ary){
    bool success = arraylist_reserve(lst, lst->length + len);
    if(success){
        size_t i;
        for(i = lst->length + len; i > ind + len; i--){
            lst->list[i] = lst->list[i - 1];
        }
        for(i = ind + len; i > ind; i--){
            lst->list[i] = ary[i];
        }
    }
    return success;
}

/**
 * Removes the data at the specified index from the list and returns the removed
 * data pointer
 * @param lst  The arraylist to remove from
 * @param ind  The index of the element to remove
 * @return  The removed element
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
 * Delete all elements in the array. Does not release any memory
 * @param  lst The arraylist to clear
 */
void arraylist_clear(arraylist_t* lst){
    size_t i;
    for(i = 0; i < lst->length; i++){
        lst->list[i] = NULL;
    }
    lst->length = 0;
}

/**
 * Returns the number of items in the arraylist
 * @param lst  The arraylist
 * @return  The length of the given arraylist
 */
size_t arraylist_length(const arraylist_t* lst){
    return lst->length;
}

/**
 * Returns a pointer to the dynamic array contained in this arraylist
 * @param lst  The arraylist
 * @return  The array held by the given arraylist
 */
void** arraylist_toarray(const arraylist_t* lst){
    return lst->list;
}

/**
 * Returns the item at the specified index of the arraylist
 * @param lst  The arraylist to look in
 * @param ind  The index of the element to get
 * @return  The element at the specified index
 */
void* arraylist_get(const arraylist_t* lst, const size_t ind){
    return lst->list[ind];
}

/**
 * Searches the arraylist for the specified item using the given comparator
 * function to check for equality. Returns the index at which the item was found
 * or -1 if it was not found
 */
ptrdiff_t arraylist_indexof(const arraylist_t* lst, const void* data, 
                            int (*cmp) (const void*, const void*)){
    size_t i = 0;
    while(i < lst->length && (*cmp)(data, lst->list[i]) != 0){
        i++;
    }
    return i < lst->length ? i : -1;
}
