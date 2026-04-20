#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "permutations.h"
#include "minunit.h"

/* --- Permutations Example --- */

// This example demonstrates the permutation generation functionality.
// It shows how to generate permutations of an array of integers.

// Helper function to print an array
void print_array(int *arr, size_t size) {
    printf("[");
    for (size_t i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]");
}

// Callback function to process each generated permutation
void process_permutation(int *perm, size_t size, void *user_data) {
    int *count = (int *)user_data;
    printf("Permutation %d: ", (*count) + 1);
    print_array(perm, size);
    printf("
");
    (*count)++;
}

char *test_permutation_generation() {
    int arr[] = {1, 2, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int count = 0;

    printf("
Generating permutations for [1, 2, 3]:
");

    // Generate permutations
    // The permute_array function will call process_permutation for each result.
    int result = permute_array(arr, size, process_permutation, &count);

    mu_assert("permute_array failed", result == 0); // Assuming 0 indicates success
    mu_assert("Incorrect number of permutations generated", count == 6); // 3! = 6 permutations

    printf("
Generating permutations for [A, B] (using integers to represent chars):
");
    int arr2[] = {1, 2}; // Representing 'A', 'B'
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    count = 0;
    result = permute_array(arr2, size2, process_permutation, &count);
    mu_assert("permute_array failed for second array", result == 0);
    mu_assert("Incorrect number of permutations generated for second array", count == 2); // 2! = 2 permutations

    // Test with an empty array (should do nothing or handle gracefully)
    printf("
Generating permutations for empty array:
");
    int empty_arr[] = {};
    size_t empty_size = 0;
    count = 0;
    result = permute_array(empty_arr, empty_size, process_permutation, &count);
    mu_assert("permute_array with empty array failed", result == 0);
    mu_assert("Permutations generated for empty array", count == 0);


    return NULL;
}

// Minunit runner for permutations tests
char *(*all_tests[])() = {
    test_permutation_generation,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
