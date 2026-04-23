#include <stdio.h>
#include <stdlib.h>

#include "../src/hash.h"
#include "../src/stringlib.h"

int main()
{
	HashMap h;
	if (hashmap_init(&h) == HASHMAP_FAILURE) {
		fprintf(stderr, "Failed to initialize hashmap.\n");
		return 1;
	}

	printf("Hashmap initialized.\n");
	printf("\n");

	printf("Setting key-value pairs...\n");
	printf("\n");
	hashmap_set_int(&h, "apple", 10);
	hashmap_set_int(&h, "banana", 25);
	hashmap_set_int(&h, "cherry", 5);
	hashmap_set_int(&h, "date", 15);
	hashmap_set_int(&h, "elderberry", 30);

	printf("\nRetrieving values:\n");
	int *val_apple = (int*)hashmap_get(&h, "apple");
	if (val_apple) {
		printf("Value for 'apple': %d\n", *val_apple);
	} else {
		printf("'apple' not found.\n");
	}

	int *val_banana = (int*)hashmap_get(&h, "banana");
	if (val_banana) {
		printf("Value for 'banana': %d\n", *val_banana);
	} else {
		printf("'banana' not found.\n");
	}

	// Try to get a non-existent key
	int *val_grape = (int*)hashmap_get(&h, "grape");
	if (val_grape) {
		printf("Value for 'grape': %d\n", *val_grape);
	} else {
		printf("'grape' not found.\n");
	}

	// Remove an entry
	printf("\nRemoving 'cherry'...\n");
	void* removed_val = hashmap_remove(&h, "cherry");
	if (removed_val) {
		printf("Removed 'cherry'. Value was: %d\n", *(int*)removed_val);
		free(removed_val); // Free the memory for the removed value
	} else {
		printf("'cherry' not found for removal.\n");
	}

	// Verify removal
	int* val_cherry = (int*)hashmap_get(&h, "cherry");
	if (val_cherry) {
		printf("Value for 'cherry' after removal: %d\n", *val_cherry);
	} else {
		printf("'cherry' not found after removal.\n");
	}

	// Print hashmap statistics
	printf("\nHashmap stats:\n");
	hashmap_stats(&h);

	// Destroy the hashmap and free all allocated memory
	hashmap_destroy(&h);
	printf("\nHashmap destroyed.\n");

	return 0;
}
