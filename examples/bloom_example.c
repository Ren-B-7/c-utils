#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bloom.h"
#include "minunit.h"

/* --- Bloom Filter Example --- */

// This example demonstrates the Bloom filter.
// It shows how to create a Bloom filter, add elements,
// and check for their potential presence.

char *test_bloom_add_and_check() {
    // Create a Bloom filter with a capacity for 1000 elements and a false positive rate of 0.1%
    bloom_t *bloom = bloom_create(1000, 0.001);
    mu_assert("bloom_create failed", bloom != NULL);

    // Add elements to the filter
    char *item1 = "apple";
    char *item2 = "banana";
    char *item3 = "grape";

    bloom_add(bloom, item1);
    bloom_add(bloom, item2);
    bloom_add(bloom, item3);

    // Check for presence of elements that were added
    mu_assert("bloom_check failed for 'apple'", bloom_check(bloom, item1) == true);
    mu_assert("bloom_check failed for 'banana'", bloom_check(bloom, item2) == true);
    mu_assert("bloom_check failed for 'grape'", bloom_check(bloom, item3) == true);

    // Check for presence of an element that was NOT added
    char *item4 = "orange";
    // Note: Bloom filters can have false positives, so this might occasionally return true,
    // but it should ideally be false for distinct, non-added items.
    mu_assert("bloom_check returned true for non-existent item (potential false positive)", bloom_check(bloom, item4) == false); // This is the ideal case

    bloom_destroy(bloom); // Clean up
    return NULL;
}

char *test_bloom_false_positive_scenario() {
    // This test is designed to illustrate a potential false positive.
    // It's not guaranteed to produce one in a single run due to hash function randomness.

    // Create a small Bloom filter to increase the chance of false positives
    bloom_t *bloom = bloom_create(10, 0.1); // Small capacity, higher FP rate
    mu_assert("bloom_create failed", bloom != NULL);

    char *added_item = "test_item";
    bloom_add(bloom, added_item);

    // Check for an item that is similar or could collide through hashing
    // Finding a guaranteed false positive requires specific knowledge of hash functions
    // and is hard to demonstrate deterministically in a simple example.
    // We'll use a different string and check.
    char *potentially_colliding_item = "another_test";

    printf("Checking for '%s' (added: '%s')
", potentially_colliding_item, added_item);

    // The result of bloom_check for potentially_colliding_item is not strictly guaranteed.
    // If it returns true, it's a false positive. If false, it's correct.
    // We cannot assert a specific outcome here without knowing the hash functions.
    bool check_result = bloom_check(bloom, potentially_colliding_item);
    printf("Result for '%s': %s
", potentially_colliding_item, check_result ? "true (potential false positive)" : "false");

    bloom_destroy(bloom);
    return NULL;
}

// Minunit runner for bloom filter tests
char *(*all_tests[])() = {
    test_bloom_add_and_check,
    test_bloom_false_positive_scenario,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
