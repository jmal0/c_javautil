#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "arraylist.h"
#include "linkedlist.h"
#include "priorityqueue.h"

int cmp_str(const void* a, const void* b){
    return strcmp(*((char**) a), *((char**) b));
}

void test_arraylist(){
    // test init and length
    arraylist_t* lst = (arraylist_t*) malloc(sizeof(arraylist_t));
    arraylist_init(lst);
    assert(arraylist_length(lst) == 0);
    assert(lst->size == 8);

    // test append & get
    char* elem1 = "element 1";
    arraylist_append(lst, &elem1);
    assert(strncmp(*((char**) arraylist_get(lst, 0)), elem1, 9) == 0);

    // test add
    char* elem2 = "element 2";
    arraylist_add(lst, 1, &elem2);
    assert(strncmp(*((char**) arraylist_get(lst, 0)), elem1, 9) == 0);
    assert(strncmp(*((char**) arraylist_get(lst, 1)), elem2, 9) == 0);

    // test indexof
    assert(arraylist_indexof(lst, (void*) &elem1, cmp_str) == 0);
    assert(arraylist_indexof(lst, (void*) &elem2, cmp_str) == 1);

    // test remove
    arraylist_remove(lst, 0);
    assert(arraylist_indexof(lst, (void*) &elem2, cmp_str) == 0);

    // test resize
    arraylist_resize(lst, 16);
    assert(lst->size == 16);

    // test reserve
    arraylist_reserve(lst, 1);
    assert(lst->size == 16);
    arraylist_reserve(lst, 32);
    assert(lst->size == 32);

    // test free
    arraylist_free(lst);
    free(lst);
}

void test_linkedlist(){
    // test init and length
    linkedlist_t* lst = (linkedlist_t*) malloc(sizeof(linkedlist_t));
    linkedlist_init(lst);
    assert(linkedlist_length(lst) == 0);
    assert(lst->start == NULL);

    // test append & get
    char* elem1 = "element 1";
    assert(linkedlist_length(lst) == 0);
    linkedlist_append(lst, (void*) &elem1);
    assert(linkedlist_length(lst) == 1);
    assert(strncmp(*((char**) linkedlist_get(lst, 0)), elem1, 9) == 0);

    // test add
    char* elem2 = "element 2";
    linkedlist_add(lst, 1, (void*) &elem2);
    assert(linkedlist_length(lst) == 2);
    assert(strncmp(*((char**) linkedlist_get(lst, 0)), elem1, 9) == 0);
    assert(strncmp(*((char**) linkedlist_get(lst, 1)), elem2, 9) == 0);

    // test indexof
    assert(linkedlist_indexof(lst, (void*) &elem1, cmp_str) == 0);
    assert(linkedlist_indexof(lst, (void*) &elem2, cmp_str) == 1);

    // test remove
    linkedlist_remove(lst, 0);
    assert(linkedlist_length(lst) == 1);
    assert(linkedlist_indexof(lst, (void*) &elem2, cmp_str) == 0);
    char* elem3 = "element 3";
    linkedlist_append(lst, (void*) &elem3);
    assert(linkedlist_length(lst) == 2);
    assert(linkedlist_remove(lst, 1) != NULL);
    assert(linkedlist_length(lst) == 1);
    assert(linkedlist_indexof(lst, (void*) &elem3, cmp_str) == -1);

    // test free
    linkedlist_free(lst);
    free(lst);
}

void test_priorityqueue(){
    // test init and length
    priorityqueue_t* pq = (priorityqueue_t*) malloc(sizeof(priorityqueue_t));
    priorityqueue_init(pq, cmp_str);
    assert(priorityqueue_size(pq) == 0);

    // test add & peek
    char* elem2 = "element 2";
    priorityqueue_add(pq, (void*) &elem2);
    char* elem1 = "element 1";
    priorityqueue_add(pq, (void*) &elem1);
    assert(priorityqueue_size(pq) == 2);
    assert(strncmp(*((char**) priorityqueue_peek(pq)), elem1, 9) == 0);

    // test poll and validate heap
    assert(strncmp(*((char**) priorityqueue_poll(pq)), elem1, 9) == 0);
    assert(priorityqueue_size(pq) == 1);
    assert(strncmp(*((char**) priorityqueue_peek(pq)), elem2, 9) == 0);
    assert(validate_heap(pq));

    // test addall
    char* e1 = "1";
    char* e2 = "2";
    char* e3 = "3";
    char* e4 = "4";
    char* e5 = "5";
    char* e6 = "6";
    char* e7 = "7";
    char* e8 = "8";
    void* elems[8] = {&e4, &e1, &e7, &e6, &e3, &e5, &e2, &e8};
    priorityqueue_addall(pq, elems, 8);
    assert(priorityqueue_size(pq) == 9);
    assert(strncmp(*((char**) priorityqueue_peek(pq)), "1", 9) == 0);
    assert(validate_heap(pq));

    // test remove
    priorityqueue_remove(pq, &e1);
    assert(strncmp(*((char**) priorityqueue_peek(pq)), "2", 9) == 0);
    assert(priorityqueue_size(pq) == 8);
    assert(validate_heap(pq));

    // test free
    priorityqueue_free(pq);
    free(pq);
}

int main(int argc, char const *argv[]){
    printf("Testing arraylist\n");
    test_arraylist();
    printf("Arraylist passed tests\n");

    printf("Testing linkedlist\n");
    test_linkedlist();
    printf("Linkedlist passed tests\n");

    printf("Testing priorityqueue\n");
    test_priorityqueue();
    printf("Priorityqueue passed tests\n");
    return 0;
}
