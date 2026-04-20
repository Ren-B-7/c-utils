#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitarray.h"
#include "minunit.h"

/* --- Bitarray Example --- */

// This example demonstrates the bitarray functionality.
// It shows how to create a bitarray, set and get bits, and check its size.

char *test_bitarray_operations() {
    // Create a bitarray to hold 32 bits
    bitarray_t *ba = bitarray_create(32);
    mu_assert("bitarray_create failed", ba != NULL);

    // Set some bits
    bitarray_set(ba, 0);  // Set the 0th bit
    bitarray_set(ba, 5);  // Set the 5th bit
    bitarray_set(ba, 31); // Set the 31st bit

    // Get bits and check their values
    mu_assert("bitarray_get failed for bit 0", bitarray_get(ba, 0) == 1);
    mu_assert("bitarray_get failed for bit 5", bitarray_get(ba, 5) == 1);
    mu_assert("bitarray_get failed for bit 31", bitarray_get(ba, 31) == 1);
    mu_assert("bitarray_get failed for bit 10 (should be 0)", bitarray_get(ba, 10) == 0);

    // Test setting a bit that is already set
    bitarray_set(ba, 5);
    mu_assert("bitarray_set on already set bit failed", bitarray_get(ba, 5) == 1);

    // Test clearing a bit
    bitarray_clear(ba, 5);
    mu_assert("bitarray_clear failed for bit 5", bitarray_get(ba, 5) == 0);

    // Test clearing a bit that is already clear
    bitarray_clear(ba, 10);
    mu_assert("bitarray_clear on already clear bit failed", bitarray_get(ba, 10) == 0);

    // Check the size of the bitarray
    mu_assert("bitarray_size incorrect", bitarray_size(ba) == 32);

    // Test bitarray_resize to a larger size
    bitarray_t *ba_resized = bitarray_resize(ba, 64);
    mu_assert("bitarray_resize failed", ba_resized != NULL);
    mu_assert("bitarray_size incorrect after resize", bitarray_size(ba_resized) == 64);
    mu_assert("bitarray_get failed after resize for existing bit", bitarray_get(ba_resized, 0) == 1);
    mu_assert("bitarray_get failed after resize for cleared bit", bitarray_get(ba_resized, 5) == 0);
    mu_assert("bitarray_get failed after resize for unset bits", bitarray_get(ba_resized, 40) == 0);

    // Set a new bit in the resized array
    bitarray_set(ba_resized, 40);
    mu_assert("bitarray_get failed for newly set bit after resize", bitarray_get(ba_resized, 40) == 1);

    bitarray_destroy(ba_resized); // Destroy the resized bitarray

    return NULL;
}

// Minunit runner for bitarray tests
char *(*all_tests[])() = {
    test_bitarray_operations,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
