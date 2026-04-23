#ifndef BARRUST_ARENA_H__
#define BARRUST_ARENA_H__

#include <assert.h>
#include <stddef.h>

typedef struct {
	void* base;
	size_t size;
	size_t offset;
	size_t peak;
} arena_t;

arena_t arena_new(size_t size);
void* arena_alloc(arena_t* a, size_t nbytes);
void* arena_alloc_zero(arena_t* a, size_t nbytes);
void arena_stats(const arena_t* a);
void arena_free(arena_t* a);

typedef size_t arena_checkpoint_t;

static inline arena_checkpoint_t arena_save(const arena_t* a)
{
	return a->offset;
}

static inline void arena_restore(arena_t* a, arena_checkpoint_t cp)
{
	assert(cp <= a->offset && "arena_restore: checkpoint error");
	a->offset = cp;
}

#endif
