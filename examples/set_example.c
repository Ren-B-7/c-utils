#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"
#include "minunit.h"

/* --- Set Example --- */

// A simple example to demonstrate set functionality.
// This example creates a set, inserts elements, checks for existence,
// and demonstrates removal.

char *test_set_insert_and_contains() {
    set_t *s = set_create(10); // Create a set with capacity 10
    mu_assert("set_create failed", s != NULL);

    // Insert elements
    mu_assert("set_insert failed for 'apple'", set_insert(s, "apple") == SUCCESS);
    mu_assert("set_insert failed for 'banana'", set_insert(s, "banana") == SUCCESS);
    mu_assert("set_insert failed for 'grape'", set_insert(s, "grape") == SUCCESS);

    // Check for existence
    mu_assert("set_contains failed for 'apple'", set_contains(s, "apple") == true);
    mu_assert("set_contains failed for 'banana'", set_contains(s, "banana") == true);
    mu_assert("set_contains failed for 'grape'", set_contains(s, "grape") == true);
    mu_assert("set_contains returned true for non-existent key", set_contains(s, "orange") == false);

    // Test inserting a duplicate element
    mu_assert("set_insert allowed duplicate", set_insert(s, "apple") == ALREADY_EXISTS);

    set_destroy(s); // Clean up
    return NULL;
}

char *test_set_remove() {
    set_t *s = set_create(5);
    mu_assert("set_create failed", s != NULL);

    set_insert(s, "key1");
    set_insert(s, "key2");

    mu_assert("set_contains failed before remove", set_contains(s, "key1") == true);

    set_remove(s, "key1"); // Remove an element

    mu_assert("set_contains still found removed key", set_contains(s, "key1") == false);
    mu_assert("set_contains failed for existing key after remove", set_contains(s, "key2") == true);
    mu_assert("set_remove failed for non-existent key", set_remove(s, "nonexistent_key") == NOT_FOUND);

    set_destroy(s);
    return NULL;
}

char *test_set_resize() {
    set_t *s = set_create(2); // Small initial capacity to force resize
    mu_assert("set_create failed", s != NULL);

    // Insert enough elements to trigger a resize
    set_insert(s, "a");
    set_insert(s, "b");
    set_insert(s, "c"); // Should trigger resize
    set_insert(s, "d");
    set_insert(s, "e");

    // Check if elements are still retrievable after resize
    mu_assert("set_contains failed after resize for 'a'", set_contains(s, "a") == true);
    mu_assert("set_contains failed after resize for 'c'", set_contains(s, "c") == true);
    mu_assert("set_contains failed after resize for 'e'", set_contains(s, "e") == true);

    set_destroy(s);
    return NULL;
}

// Minunit runner for set tests
char *(*all_tests[])() = {
    test_set_insert_and_contains,
    test_set_remove,
    test_set_resize,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
