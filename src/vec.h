#ifndef BARRUST_VEC_H__
#define BARRUST_VEC_H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define VEC_GROW_FACTOR 2
#define VEC_INITIAL_CAP 8

#define VEC_DECL(TypeName, ItemType)                                           \
  typedef struct {                                                             \
    ItemType *data;                                                            \
    size_t len;                                                                \
    size_t cap;                                                                \
  } TypeName

VEC_DECL(vec_t, void *);

#define VEC_PUSH(vec, item)                                                    \
  do {                                                                         \
    if ((vec).len >= (vec).cap) {                                              \
      size_t _new_cap =                                                        \
          (vec).cap == 0 ? VEC_INITIAL_CAP : (vec).cap * VEC_GROW_FACTOR;      \
      (vec).data = realloc((vec).data, _new_cap * sizeof(*(vec).data));        \
      assert((vec).data != NULL && "VEC_PUSH: realloc failed");                \
      (vec).cap = _new_cap;                                                    \
    }                                                                          \
    (vec).data[(vec).len++] = (item);                                          \
  } while (0)

#define VEC_POP(vec)                                                           \
  (assert((vec).len > 0 && "VEC_POP: vec is empty"), (vec).data[--(vec).len])

#define VEC_FIRST(vec)                                                         \
  (assert((vec).len > 0 && "VEC_FIRST: vec is empty"), (vec).data[0])

#define VEC_LAST(vec)                                                          \
  (assert((vec).len > 0 && "VEC_LAST: vec is empty"), (vec).data[(vec).len - 1])

#define VEC_GET(vec, idx)                                                      \
  (assert((idx) < (vec).len && "VEC_GET: index out of bounds"),                \
   (vec).data[(idx)])

#define VEC_SET(vec, idx, val)                                                 \
  do {                                                                         \
    assert((idx) < (vec).len && "VEC_SET: index out of bounds");               \
    (vec).data[(idx)] = (val);                                                 \
  } while (0)

#define VEC_AT(vec, idx) ((vec).data[(idx)])

#define VEC_INSERT(vec, idx, item)                                             \
  do {                                                                         \
    assert((idx) <= (vec).len && "VEC_INSERT: index out of bounds");           \
    VEC_PUSH(vec, (item));                                                     \
    if ((idx) < (vec).len - 1) {                                               \
      memmove(&(vec).data[(idx) + 1], &(vec).data[(idx)],                      \
              ((vec).len - 1 - (idx)) * sizeof(*(vec).data));                  \
    }                                                                          \
    (vec).data[(idx)] = (item);                                                \
  } while (0)

#define VEC_REMOVE(vec, idx)                                                   \
  do {                                                                         \
    assert((idx) < (vec).len && "VEC_REMOVE: index out of bounds");            \
    if ((idx) < (vec).len - 1) {                                               \
      memmove(&(vec).data[(idx)], &(vec).data[(idx) + 1],                      \
              ((vec).len - (idx) - 1) * sizeof(*(vec).data));                  \
    }                                                                          \
    (vec).len--;                                                               \
  } while (0)

#define VEC_REMOVE_FAST(vec, idx)                                              \
  do {                                                                         \
    assert((idx) < (vec).len && "VEC_REMOVE_FAST: index out of bounds");       \
    (vec).data[(idx)] = (vec).data[--(vec).len];                               \
  } while (0)

#define VEC_FOREACH(ItemType, v, vec)                                          \
  for (ItemType *v = (vec).data; v < (vec).data + (vec).len; ++v)

#define VEC_SORT(vec, cmp_fn)                                                  \
  qsort((vec).data, (vec).len, sizeof(*(vec).data), (cmp_fn))

#define VEC_CLEAR(vec) ((vec).len = 0)

#define VEC_ZERO(vec)                                                          \
  do {                                                                         \
    if ((vec).data)                                                            \
      memset((vec).data, 0, (vec).cap * sizeof(*(vec).data));                  \
    (vec).len = 0;                                                             \
  } while (0)

#define VEC_SHRINK(vec)                                                        \
  do {                                                                         \
    if ((vec).len < (vec).cap && (vec).len > 0) {                              \
      (vec).data = realloc((vec).data, (vec).len * sizeof(*(vec).data));       \
      (vec).cap = (vec).len;                                                   \
    }                                                                          \
  } while (0)

#define VEC_RESERVE(vec, min_cap)                                              \
  do {                                                                         \
    if ((vec).cap < (size_t)(min_cap)) {                                       \
      (vec).data = realloc((vec).data, (min_cap) * sizeof(*(vec).data));       \
      assert((vec).data != NULL && "VEC_RESERVE: realloc failed");             \
      (vec).cap = (min_cap);                                                   \
    }                                                                          \
  } while (0)

#define VEC_FREE(vec)                                                          \
  do {                                                                         \
    free((vec).data);                                                          \
    (vec).data = NULL;                                                         \
    (vec).len = 0;                                                             \
    (vec).cap = 0;                                                             \
  } while (0)

#endif
