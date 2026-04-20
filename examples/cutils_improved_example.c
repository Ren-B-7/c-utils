/*
 * cutils_improved_example.c — demonstrates new cutils units
 *
 * Compile:
 *     make examples
 */

#include "../src/macros.h"
#include "../src/vec.h"
#include "../src/arena.h"
#include "../src/hash.h"
#include "../src/result.h"
#include "../src/logger.h"
#include <stdio.h>
#include <stdint.h>

static int cmp_desc(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

static void demo_vector(void) {
    printf("\n=== Vector (vec.h) ===\n");
    VEC_DECL(IntVec, int);
    IntVec nums = {0};

    for (int i = 0; i < 8; i++) VEC_PUSH(nums, i * i);
    printf("len=%zu  first=%d  last=%d\n", nums.len, VEC_FIRST(nums), VEC_LAST(nums));

    printf("values: ");
    VEC_FOREACH(int, v, nums) printf("%d ", *v);
    printf("\n");

    VEC_INSERT(nums, 3, 999);
    VEC_REMOVE(nums, 3);
    VEC_SORT(nums, cmp_desc);
    
    printf("popped: %d\n", VEC_POP(nums));
    VEC_FREE(nums);
}

static void demo_hash(void) {
    printf("\n=== Hash Table (hash.h) ===\n");
    hash_t config = hash_new(64);
    hash_set(&config, "host", (void*)"localhost");
    
    printf("host: %s\n", (const char*)hash_get(&config, "host"));
    hash_free(&config);
}

static void demo_bits(void) {
    printf("\n=== Bit Operations (macros.h) ===\n");
    uint8_t flags = 0;
    BIT_SET(flags, 3);
    printf("bit 3 set: %d\n", BIT_TST(flags, 3));
    BIT_TOG(flags, 3);
    printf("bit 3 toggled: %d\n", BIT_TST(flags, 3));
}

static void demo_arena(void) {
    printf("\n=== Arena (arena.h) ===\n");
    arena_t a = arena_new(1024);
    int *n = (int*)arena_alloc(&a, sizeof(int));
    *n = 42;
    printf("value: %d\n", *n);
    arena_free(&a);
}

static result_t test_res(int v) {
    return v > 0 ? result_ok() : result_err("must be positive");
}

static void demo_result(void) {
    printf("\n=== Result (result.h) ===\n");
    result_t r = test_res(-1);
    if (!r.ok) printf("error: %s\n", r.msg);
}

static void demo_logger(void) {
    printf("\n=== Logger (logger.h) ===\n");
    log_init(LOG_DEBUG, NULL);
    LOG_INFO("Logger initialized and working");
    log_close();
}

int main(void) {
    demo_vector();
    demo_hash();
    demo_bits();
    demo_arena();
    demo_result();
    demo_logger();
    return 0;
}
