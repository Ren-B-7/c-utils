#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/arena.h" // Include arena header

/* --- Arena Allocator Example --- */

// This example demonstrates the arena allocator.
// It shows how to create an arena, allocate memory from it,
// and then restore or free the arena.

int main()
{
	printf("--- Arena Allocator Example ---\n");

	// Create an arena with 1KB capacity
	arena_t arena = arena_new(1024);
	if (arena.base == NULL) {
		fprintf(stderr, "Error: arena_new failed.\n");
		return 1;
	}
	printf("Arena created with capacity 1024 bytes.\n");

	// Allocate memory from the arena
	printf("Allocating memory from arena...\n");
	char* data1 = arena_alloc(&arena, 50);
	char* data2 = arena_alloc(&arena, 100);

	if (data1 == NULL) {
		fprintf(stderr, "Error: arena_alloc failed for data1.\n");
		arena_free(&arena);
		return 1;
	}
	if (data2 == NULL) {
		fprintf(stderr, "Error: arena_alloc failed for data2.\n");
		arena_free(&arena);
		return 1;
	}
	printf("Allocated 50 bytes for data1 and 100 bytes for data2.\n");

	// Copy data into allocated buffers (example)
	strcpy(data1, "Hello Arena!");
	strcpy(data2, "Another piece of data.");

	printf("Arena data 1: %s\n", data1);
    printf("Arena data 2: %s\n", data2);

    // Demonstrate arena_restore (checkpointing)
    printf("Demonstrating arena restore...\n");
    arena_checkpoint_t cp = arena_save(&arena);
    printf("Saved checkpoint at offset: %zu\n", cp);

    char* data3 = arena_alloc(&arena, 40);
    if (data3 == NULL) {
        fprintf(stderr, "Error: arena_alloc failed for data3.\n");
        arena_free(&arena);
        return 1;
    }
    strcpy(data3, "Temporary data.");
    printf("Allocated data3: %s\n", data3);

    // Restore to the checkpoint, invalidating data3
    arena_restore(&arena, cp);
    printf("Restored arena to checkpoint (offset %zu).\n", arena_save(&arena));

    // Attempt to allocate again after restore
    char* data4 = arena_alloc(&arena, 30);
    if (data4 == NULL) {
        fprintf(stderr, "Error: arena_alloc failed for data4 after restore.\n");
        arena_free(&arena);
        return 1;
    }
    strcpy(data4, "New data after restore.");
    printf("Allocated data4: %s\n", data4);
    // data3 is now dangling and should not be used.

    // Free the arena
    printf("Freeing arena...\n");
    arena_free(&arena);
	printf("Arena example finished.\n");

	return 0;
}


