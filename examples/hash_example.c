#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "minunit.h"

/* --- Hash Example --- */

// A simple example to demonstrate hash table functionality.
// This example creates a hash table, inserts key-value pairs,
// retrieves values, and demonstrates deletion.

char *test_hash_insert_and_get() {
    hash_table_t *ht = hash_create(10); // Create a hash table with capacity 10
    mu_assert("hash_create failed", ht != NULL);

    // Insert key-value pairs
    hash_insert(ht, "apple", "red");
    hash_insert(ht, "banana", "yellow");
    hash_insert(ht, "grape", "purple");

    // Retrieve values
    mu_assert("hash_get failed for 'apple'", strcmp(hash_get(ht, "apple"), "red") == 0);
    mu_assert("hash_get failed for 'banana'", strcmp(hash_get(ht, "banana"), "yellow") == 0);
    mu_assert("hash_get failed for 'grape'", strcmp(hash_get(ht, "grape"), "purple") == 0);
    mu_assert("hash_get returned non-null for non-existent key", hash_get(ht, "orange") == NULL);

    // Test updating a value
    hash_insert(ht, "apple", "green"); // Update value for "apple"
    mu_assert("hash_update failed", strcmp(hash_get(ht, "apple"), "green") == 0);

    hash_destroy(ht); // Clean up
    return NULL;
}

char *test_hash_delete() {
    hash_table_t *ht = hash_create(5);
    mu_assert("hash_create failed", ht != NULL);

    hash_insert(ht, "key1", "value1");
    hash_insert(ht, "key2", "value2");

    mu_assert("hash_get failed before delete", hash_get(ht, "key1") != NULL);

    hash_delete(ht, "key1"); // Delete an entry

    mu_assert("hash_get still found deleted key", hash_get(ht, "key1") == NULL);
    mu_assert("hash_get failed for existing key after delete", strcmp(hash_get(ht, "key2"), "value2") == 0);

    hash_destroy(ht);
    return NULL;
}

char *test_hash_resize() {
    hash_table_t *ht = hash_create(2); // Small initial capacity to force resize
    mu_assert("hash_create failed", ht != NULL);

    // Insert enough elements to trigger a resize
    hash_insert(ht, "a", "1");
    hash_insert(ht, "b", "2");
    hash_insert(ht, "c", "3"); // Should trigger resize
    hash_insert(ht, "d", "4");
    hash_insert(ht, "e", "5");

    // Check if elements are still retrievable after resize
    mu_assert("hash_get failed after resize for 'a'", strcmp(hash_get(ht, "a"), "1") == 0);
    mu_assert("hash_get failed after resize for 'c'", strcmp(hash_get(ht, "c"), "3") == 0);
    mu_assert("hash_get failed after resize for 'e'", strcmp(hash_get(ht, "e"), "5") == 0);

    hash_destroy(ht);
    return NULL;
}

// Minunit runner for hash tests
char *(*all_tests[])() = {
    test_hash_insert_and_get,
    test_hash_delete,
    test_hash_resize,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
