#include <stdio.h>
#include <stdlib.h>

#include "arena.h"
#include "minunit.h"

/* --- Arena Allocator Example --- */

// This example demonstrates the arena allocator.
// It shows how to create an arena, allocate memory from it,
// and then reset or destroy the arena.

char *test_arena_allocation() {
    arena_t *arena = arena_create(1024); // Create an arena with 1KB capacity
    mu_assert("arena_create failed", arena != NULL);

    // Allocate memory from the arena
    char *data1 = arena_alloc(arena, 50);
    char *data2 = arena_alloc(arena, 100);
    mu_assert("arena_alloc failed for data1", data1 != NULL);
    mu_assert("arena_alloc failed for data2", data2 != NULL);

    // Check if allocations are within the arena bounds (conceptual check)
    // In a real scenario, you'd have more checks or rely on the allocator's internal logic.

    // Copy data into allocated buffers (example)
    strcpy(data1, "Hello Arena!");
    strcpy(data2, "Another piece of data.");

    printf("Arena data 1: %s
", data1);
    printf("Arena data 2: %s
", data2);

    // Arena is automatically reset or destroyed.
    // For this example, we'll demonstrate destruction.
    arena_destroy(arena);
    return NULL;
}

char *test_arena_reset() {
    arena_t *arena = arena_create(512);
    mu_assert("arena_create failed", arena != NULL);

    char *data1 = arena_alloc(arena, 20);
    mu_assert("arena_alloc failed", data1 != NULL);
    strcpy(data1, "Some data");

    printf("Data before reset: %s
", data1);

    arena_reset(arena); // Reset the arena, all previous allocations are now invalid

    // Attempt to allocate again from the reset arena
    char *data2 = arena_alloc(arena, 30);
    mu_assert("arena_alloc failed after reset", data2 != NULL);
    strcpy(data2, "New data after reset");

    printf("Data after reset: %s
", data2);
    // data1 is now dangling and should not be used.

    arena_destroy(arena);
    return NULL;
}

// Minunit runner for arena tests
char *(*all_tests[])() = {
    test_arena_allocation,
    test_arena_reset,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
