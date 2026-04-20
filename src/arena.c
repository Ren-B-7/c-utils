#include "arena.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

arena_t arena_new(size_t size) {
  arena_t a;
  a.base = malloc(size);
  assert(a.base != NULL);
  a.size = size; a.offset = 0; a.peak = 0;
  return a;
}

void *arena_alloc(arena_t *a, size_t nbytes) {
  if (a->offset + nbytes > a->size) abort();
  void *ptr = (char *)a->base + a->offset;
  a->offset += nbytes;
  if (a->offset > a->peak) a->peak = a->offset;
  return ptr;
}

void *arena_alloc_zero(arena_t *a, size_t nbytes) {
  void *ptr = arena_alloc(a, nbytes);
  memset(ptr, 0, nbytes);
  return ptr;
}

void arena_stats(const arena_t *a) {
  printf("[arena] size=%zu offset=%zu peak=%zu\n", a->size, a->offset, a->peak);
}

void arena_free(arena_t *a) {
  free(a->base);
  a->base = NULL; a->size = 0; a->offset = 0; a->peak = 0;
}
