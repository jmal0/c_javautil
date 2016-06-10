/*
 c priority queue data structure based on a min heap
*/
#include "priorityqueue.h"

const size_t priorityqueue_init_size = 16;  
const size_t priorityqueue_resize_factor = 2; 

/**
 *
 */
bool priorityqueue_init(priorityqueue_t* pq,
                        int (*comparator)(const void*, const void*)){
    pq->data = (void**) malloc(priorityqueue_init_size*sizeof(void*));
    pq->length = 0;
    pq->size = priorityqueue_init_size;
    pq->cmp = comparator;
    return pq->data != NULL;
}

/**
 *
 */
void priorityqueue_free(priorityqueue_t* pq){
    if(pq->data){
        free(pq->data);
    }
}

/**
 *
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
 *
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
 *
 */
void priorityqueue_clear(priorityqueue_t* pq){
    size_t i;
    for(i = 0; i < pq->size; i++){
        pq->data[i] = NULL;
    }
    pq->length = 0;
}

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
 *
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
 *
 */
size_t priorityqueue_size(const priorityqueue_t* pq){
    return pq->length;
}

/**
 *
 */
void** priorityqueue_toarray(const priorityqueue_t* pq){
    return pq->data;
}
/**
 *
 */
void* priorityqueue_peek(const priorityqueue_t* pq){
    return pq->data[0];
}

/**
 *
 */
bool validate_heap(const void** data, const size_t length, 
                    int (*cmp)(const void*, const void*)){
    size_t i;
    for(i = length-1; i > 0; i--){
        if(cmp(data[i], data[_PQ_PARENT(i)]) < 0){
            return false;
        }
    }
    return true;
}
