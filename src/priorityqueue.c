/*
 c priority queue data structure based on a min heap
*/
#include "priorityqueue.h"

const size_t priorityqueue_init_size = 16;  
const size_t priorityqueue_resize_factor = 2; 

/**
 * Initialize a priority queue with a given comparator function for its elements
 * @param pq   The priority queue pointer to initialize
 * @param cmp  The compare function for the queue. Must take pointers to queue
 *             elements and return an integer
 */
bool priorityqueue_init(priorityqueue_t* pq,
                        int (*cmp)(const void*, const void*)){
    pq->data = (void**) malloc(priorityqueue_init_size*sizeof(void*));
    pq->length = 0;
    pq->size = priorityqueue_init_size;
    pq->cmp = cmp;
    return pq->data != NULL;
}

/**
 * Free the memory held by a priority queue
 * <p>
 * This function should be called when the priority queue is no longer needed
 * and before freeing the pointer itself
 * @param pq  The pointer to the queue whose memory should be released
 */
void priorityqueue_free(priorityqueue_t* pq){
    if(pq->data){
        free(pq->data);
    }
}

/**
 * Ensure that sufficient memory is allocated for the queue to hold the
 * specified amount of memory
 * <p>
 * The queue is only resized by factors of two, so the actual size of the array 
 * will be the next largest power of two after size
 * @param pq    The priority queue to allocate memory for
 * @param size  The number of elements to ensure space is allocated for
 * @return  t/f depending on the successful allocation of the requested space
 */
bool priorityqueue_reserve(priorityqueue_t* pq, size_t size){
    if(pq->size < size){
        while(pq->size < size){
            pq->size *= priorityqueue_resize_factor;
        }
        pq->data = (void**) realloc(pq->data, pq->size*sizeof(void*));
    }
    return pq->data != NULL;
}   

/**
 * Add an element to the queue with natural priority (from comparator)
 * @param pq    The queue to add to
 * @param elem  The pointer to the element to add
 * @return  t/f depending on the successful allocation of the requested space
 */
bool priorityqueue_add(priorityqueue_t* pq, void* elem){
    bool success = priorityqueue_reserve(pq, pq->length + 1);
    if(success){
        size_t ind = pq->length;
        pq->data[ind] = elem;
        pq->length++;
        while(ind > 0){
            if(pq->cmp(pq->data[ind], pq->data[_PQ_PARENT(ind)]) < 0){
                // Swap
                pq->data[ind] = pq->data[_PQ_PARENT(ind)];
                pq->data[_PQ_PARENT(ind)] = elem;
                ind = _PQ_PARENT(ind);
            }
            else{
                break;
            }
        }
    }
    return success;
}

/**
 * Add an array of elements to the queue with natural priority (from comparator)
 * @param pq     The queue to add to
 * @param elems  The array of pointers to the elements to add
 * @param size   The number of elements in the elems
 * @return  t/f depending on the successful allocation of the requested space
 */
bool priorityqueue_addall(priorityqueue_t* pq, void** elems, size_t len){
    bool success = priorityqueue_reserve(pq, pq->length + len);
    if(success){
        size_t i, ind;
        for(i = 0; i < len; i++){
            ind = pq->length;
            pq->data[ind] = elems[i];
            pq->length++;
            while(ind > 0){
                if(pq->cmp(pq->data[ind], pq->data[_PQ_PARENT(ind)]) < 0){
                    // Swap
                    pq->data[ind] = pq->data[_PQ_PARENT(ind)];
                    pq->data[_PQ_PARENT(ind)] = elems[i];
                    ind = _PQ_PARENT(ind);
                }
                else{
                    break;
                }
            }
        }
    }
    return success;
}

/**
 * Remove one occurence of the specified element from the queue if it is found
 * @param pq    The queue to remove from
 * @param elem  The pointer to the element to remove
 * W@return  Whether or not the element was removed
 */
bool priorityqueue_remove(priorityqueue_t* pq, const void* elem){
    size_t ind = 0;
    while(ind < pq->length && pq->cmp(pq->data[ind], elem) != 0){
        ind++;
    }
    if(ind == pq->length){
        return false;
    }
    
    // Grab last element and shrink list
    pq->data[ind] = pq->data[pq->length - 1];
    pq->data[pq->length - 1] = NULL;
    pq->length--;
    
    size_t min_ind = ind;
    bool swap = true;
    while(swap && ind < pq->length){
        swap = false;
        min_ind = ind;
        if(_PQ_LEFT(ind) < pq->length &&
           pq->cmp(pq->data[_PQ_LEFT(ind)], pq->data[min_ind]) < 0){
            min_ind = _PQ_LEFT(ind);
        }
        if(_PQ_RIGHT(ind) < pq->length &&
           pq->cmp(pq->data[_PQ_RIGHT(ind)], pq->data[min_ind]) < 0){
            min_ind = _PQ_RIGHT(ind);
        }
        
        if(min_ind != ind){
            void* tmp = pq->data[ind];
            pq->data[ind] = pq->data[min_ind];
            pq->data[min_ind] = tmp;
            swap = true;
        }
        ind = min_ind;
    }
    return true;
}

/**
 * Delete all elements from the queue
 * @param pq  The queue to clear
 */
void priorityqueue_clear(priorityqueue_t* pq){
    size_t i;
    for(i = 0; i < pq->size; i++){
        pq->data[i] = NULL;
    }
    pq->length = 0;
}

/**
 * Remove the minumum element from the queue and return it
 * @param pq  The queue to pop from
 * @return  The pointer to the minimum element in the queue
 */
void* priorityqueue_poll(priorityqueue_t* pq){
    if (pq->length == 0){
        return NULL;
    }

    // Grab last element and shrink list
    void* elem = pq->data[0];
    pq->data[0] = pq->data[pq->length - 1];
    pq->data[pq->length - 1] = NULL;
    pq->length--;
    
    size_t ind = 0;
    size_t min_ind = ind;
    bool swap = true;
    while(swap && ind < pq->length){
        swap = false;
        min_ind = ind;
        if(_PQ_LEFT(ind) < pq->length &&
           pq->cmp(pq->data[_PQ_LEFT(ind)], pq->data[min_ind]) < 0){
            min_ind = _PQ_LEFT(ind);
        }
        if(_PQ_RIGHT(ind) < pq->length &&
           pq->cmp(pq->data[_PQ_RIGHT(ind)], pq->data[min_ind]) < 0){
            min_ind = _PQ_RIGHT(ind);
        }
        
        if(min_ind != ind){
            void* tmp = pq->data[ind];
            pq->data[ind] = pq->data[min_ind];
            pq->data[min_ind] = tmp;
            swap = true;
        }
        ind = min_ind;
    }
    return elem;
}

/**
 * Searches the arraylist for the specified item using the queue's comparator
 * @param pq    The queue to look in
 * @param elem  The element to be found
 * @return  whether or not the item was found in the heap
 */
bool priorityqueue_contains(const priorityqueue_t* pq, const void* elem){
    size_t i;
    for(i = 0; i < pq->length; i++){
        if(pq->data[i] != NULL && pq->cmp(elem, pq->data[i]) == 0){
            return true;
        }
    }
    return false;
}

/**
 * Returns the number of elements in the heap
 * @param pq  The queue
 * @return  The number of elements in the heap
 */
size_t priorityqueue_size(const priorityqueue_t* pq){
    return pq->length;
}

/**
 * Returns the reference to the heap array held by the queue struct
 * @param pq  The queue to look in
 * @return  The array holding the elements in the queue
 */
void** priorityqueue_toarray(const priorityqueue_t* pq){
    return pq->data;
}
/**
 * Returns the minimum element in the queue without removing it
 * @param pq  The queue to look in
 * @return  The pointer to the minimum element in the heap
 */
void* priorityqueue_peek(const priorityqueue_t* pq){
    return pq->data[0];
}

/**
 * Verifies that a heap is properly ordered
 * @param pq  The queue to be checked
 * @return  t/f indicating if the heap condition is satisfied
 */
bool validate_heap(const priorityqueue_t* pq){
    size_t i;
    for(i = pq->length-1; i > 0; i--){
        if(pq->cmp(pq->data[i], pq->data[_PQ_PARENT(i)]) < 0){
            return false;
        }
    }
    return true;
}
