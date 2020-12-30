#include <stdlib.h>

#include "mymalloc.h"

/* Feel free to change/remove these variables and/or add your own. */
// Base address of the allocated heap.
static char *heap;
// Size of the complete heap.
static int heapsize;
// Next unallocated location in the heap.
static int top;
// Head of the free freelist.
static struct M* head;
// Struct with metadata
struct M {
  int size;
  struct M* next;
};


/* Initialize your memory manager to manage the given heap. */
void mymalloc_init(char *_heap, int _heapsize) {
  heap = _heap;
  heapsize = _heapsize;
  top = 0;
  /* TODO: Any other initialization you want to do */
  /* NOTE! Each call to mymalloc_init should initialize a brand new heap
     (discarding the old one), as it will be called once per test.
     Therefore, be sure to *initialize all your variables* here! */
  head = NULL;
}

/* Allocate a block of memory of the given size, or NULL if unable.

Returns: a pointer aligned to 8 bytes, or NULL if allocation failed. */
void *mymalloc(int size) {
  /* This is a dumb implementation of malloc, adapted slightly from the slides.

  You will augment this solution to make a real malloc. */

  /* Round `size` up to a multiple of 8 bytes */
  /* TODO: Make room for any extra metadata you want to store */
  size = (size + 7) / 8 * 8;
  size = size + sizeof(struct M);

  /* TODO: Implement and walk a free list before allocating off `top` as a last resort */
  struct M* curr = head;
  struct M* prev = NULL;
  while (curr != NULL){
    if (curr->size >= size) {
      if (prev == NULL) {
        head = head->next;
        curr->next = NULL;
        return (void*) curr + sizeof(struct M);
      }
      prev->next = curr->next;
      curr->next = NULL;
      return (void*) curr + sizeof(struct M);
    }
    prev = curr;
    curr = curr->next;
  }

  if(size < 0 || size > heapsize || heapsize - size < top) {
    /* There is not enough room in the heap - fail */
    return NULL;
  }

  /* Allocate the memory from `top` to `top+size` and return it */
  struct M *res = (struct M*) &heap[top];
  top += size;
  res->size = size;
  res->next = NULL;
  return (void*) res + sizeof(struct M);
}

/* Free the given block of memory. */
void myfree(void *ptr) {
  /* TODO: Our dumb implementation does not allow for any freeing. Implement me! */
  struct M* temp2 = ptr - sizeof(struct M);
  temp2 -> next = head;
  head = temp2;
    // if (head != NULL) {
    //   struct M* temp = head;
    //   head = ptr - sizeof(struct M);
    //   head->next = temp;
    //
    // } else {
    //   head = ptr - sizeof(struct M);
    // }
}
