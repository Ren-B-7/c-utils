#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec.h" // Assuming vec.h is the header for dynamic array
#include "minunit.h"

/* --- Dynamic Array (vec) Example --- */

// Minunit test for basic vec operations
char *test_vec_basic_ops() {
    vec_t *v = vec_create(5); // Create a vector with initial capacity 5
    mu_assert("vec_create failed", v != NULL);

    // Test pushing elements
    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    int val4 = 40;
    int val5 = 50;
    int val6 = 60; // This will trigger a resize

    mu_assert("vec_push failed for val1", vec_push(v, &val1) == SUCCESS);
    mu_assert("vec_push failed for val2", vec_push(v, &val2) == SUCCESS);
    mu_assert("vec_push failed for val3", vec_push(v, &val3) == SUCCESS);
    mu_assert("vec_push failed for val4", vec_push(v, &val4) == SUCCESS);
    mu_assert("vec_push failed for val5", vec_push(v, &val5) == SUCCESS);
    mu_assert("vec_size incorrect after 5 pushes", vec_size(v) == 5);
    mu_assert("vec_capacity incorrect after 5 pushes", vec_capacity(v) == 5);

    // Test pushing an element that triggers resize
    mu_assert("vec_push failed for val6 (trigger resize)", vec_push(v, &val6) == SUCCESS);
    mu_assert("vec_size incorrect after resize push", vec_size(v) == 6);
    mu_assert("vec_capacity incorrect after resize", vec_capacity(v) > 5); // Capacity should increase

    // Test accessing elements
    int *ret_val1 = (int *)vec_get(v, 0);
    int *ret_val3 = (int *)vec_get(v, 2);
    int *ret_val6 = (int *)vec_get(v, 5);

    mu_assert("vec_get failed for index 0", ret_val1 != NULL && *ret_val1 == 10);
    mu_assert("vec_get failed for index 2", ret_val3 != NULL && *ret_val3 == 30);
    mu_assert("vec_get failed for index 5", ret_val6 != NULL && *ret_val6 == 60);
    mu_assert("vec_get returned non-NULL for out of bounds index", vec_get(v, 10) == NULL);

    // Test updating an element
    int new_val3 = 35;
    mu_assert("vec_set failed", vec_set(v, 2, &new_val3) == SUCCESS);
    int *updated_val3 = (int *)vec_get(v, 2);
    mu_assert("vec_set did not update correctly", updated_val3 != NULL && *updated_val3 == 35);

    // Test popping an element
    void *popped_val = vec_pop(v);
    mu_assert("vec_pop failed", popped_val != NULL && *(int *)popped_val == 60);
    mu_assert("vec_size incorrect after pop", vec_size(v) == 5);

    // Test clear
    vec_clear(v);
    mu_assert("vec_size incorrect after clear", vec_size(v) == 0);
    mu_assert("vec_capacity incorrect after clear", vec_capacity(v) > 0); // Capacity should remain

    // Test adding elements again after clear
    mu_assert("vec_push failed after clear", vec_push(v, &val1) == SUCCESS);
    mu_assert("vec_size incorrect after push post-clear", vec_size(v) == 1);

    vec_destroy(v); // Free the vector
    return NULL;
}

// Minunit runner for vec tests
char *(*all_tests[])() = {
    test_vec_basic_ops,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
