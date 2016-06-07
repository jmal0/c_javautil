/*
 c linked list structure
*/
#include "linkedlist.h"

/**
 *
 */
void linkedlist_init(linkedlist_t* lst){
    lst->length = 0;
    lst->start = NULL;
}

/**
 *
 */
void linkedlist_free(linkedlist_t* lst){
    _llnode_t* current = lst->start;
    _llnode_t* next;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

/**
 *
 */
bool linkedlist_append(linkedlist_t* lst, void* data){
    _llnode_t* node = (_llnode_t*) malloc(sizeof(_llnode_t));
    if(node == NULL){
        return false;
    }
    node->next = NULL;
    node->data = data;

    _llnode_t* n = lst->start;
    if(n == NULL){
        lst->start = node;
        lst->length++;
        return true;
    }
    while(n->next != NULL){
        n = n->next;
    }

    n->next = node;
    lst->length++;
    return true;
}

/**
 *
 */
bool linkedlist_add(linkedlist_t* lst, const size_t ind, void* data){
    _llnode_t* node = (_llnode_t*) malloc(sizeof(_llnode_t));
    if(node == NULL){
        return false;
    }
    node->next = NULL;
    node->data = data;

    if(ind == 0){
        _llnode_t* tmp = lst->start;
        lst->start = node;
        node->next = tmp;
        lst->length++;
        return true;
    }

    _llnode_t* n = lst->start;
    if(n == NULL){
        // List is empty, while loop condition will cause null pointer exception
        return false;
    }
    size_t i = 0;
    while(i < ind-1 && n->next != NULL){
        n = n->next;
        i++;
    }

    // Add the element if we reached the correct element without a null pointer
    if(i == ind-1){
        _llnode_t* tmp = n->next;
        n->next = node;
        node->next = tmp;
        lst->length++;
        return true;
    }
    return false;
}

void* linkedlist_remove(linkedlist_t* lst, const size_t ind){
    _llnode_t* n = lst->start;
    if(n == NULL){
        // List is empty, while loop condition will cause null pointer exception
        return NULL;
    }

    if(ind == 0){
        _llnode_t* tmp = lst->start;
        void* data = tmp->data;
        lst->start = tmp->next;
        free(tmp);
        tmp = NULL;
        lst->length--;
        return data;
    }

    size_t i = 0;
    while(i < ind-1 && n != NULL){
        n = n->next;
        i++;
    }

    // Add the element if we reached the correct element without a null pointer
    if(i == ind - 1){
        _llnode_t* tmp = n->next;
        void* data = tmp->data;
        n->next = tmp->next;
        free(tmp);
        tmp = NULL;
        lst->length--;
        return data;
    }
    return NULL;
}

/**
 *
 */
size_t linkedlist_length(const linkedlist_t* lst){
    return lst->length;
}

/**
 *
 */
void** linkedlist_toarray(const linkedlist_t* lst){
    void** ary = (void**) malloc(lst->length*sizeof(void*));
    _llnode_t* current = lst->start;
    size_t i = 0;
    while(current != NULL){
        ary[i] = current->data;
        i++;
    }
    return ary;
}

/**
 *
 */
void* linkedlist_get(const linkedlist_t* lst, const size_t ind){
    _llnode_t* current = lst->start;
    size_t i = 0;
    while(i < ind && current != NULL){
        current = current->next;
        i++;
    }

    if(i == ind){
        return current->data;
    }
    return NULL;
}

/**
 *
 */
ptrdiff_t linkedlist_indexof(const linkedlist_t* lst, const void* data, 
                       int (*cmp) (const void*, const void*)){
    size_t i = 0;
    _llnode_t* current = lst->start;
    while(current != NULL && (*cmp)(data, current->data) != 0){
        current = current->next;
        i++;
    }
    return i < lst->length ? i : -1;
}
