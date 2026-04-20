#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "dllist.h" // Assuming dllist.h is the header for doubly linked list
#include "minunit.h"

/* --- Doubly Linked List (dllist) Example --- */

// Define a sample struct to store in the list
typedef struct person {
    int age;
    char gender;
    int height; /* feet */
    int id; /* order of getting here; for testing */
    char name[50]; /* Example string data */
} person_t;

// Helper function to create a new person
person_t *create_person(int id, const char *name, int age, char gender, int height) {
    person_t *p = (person_t *)malloc(sizeof(person_t));
    if (!p) return NULL;
    p->id = id;
    p->age = age;
    p->gender = gender;
    p->height = height;
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0'; // Ensure null termination
    return p;
}

// Callback function for dll_search to find a person by ID
bool find_person_by_id(void *data, void *key) {
    person_t *p = (person_t *)data;
    int *id_to_find = (int *)key;
    return p != NULL && p->id == *id_to_find;
}

// Callback function for dll_search to find a person by name
bool find_person_by_name(void *data, void *key) {
    person_t *p = (person_t *)data;
    char *name_to_find = (char *)key;
    return p != NULL && strcmp(p->name, name_to_find) == 0;
}

// Minunit test for basic dllist operations
char *test_dllist_basic_ops() {
    dllist_t l = dll_init();
    mu_assert("dll_init failed", l != NULL);

    // Test insertion at the end
    person_t *p1 = create_person(1, "Alice", 30, 'f', 5);
    person_t *p2 = create_person(2, "Bob", 25, 'm', 6);
    person_t *p3 = create_person(3, "Charlie", 35, 'm', 5);

    mu_assert("dll_insert failed for p1", dll_insert(l, p1, -1) == DLL_SUCCESS);
    mu_assert("dll_insert failed for p2", dll_insert(l, p2, -1) == DLL_SUCCESS);
    mu_assert("dll_insert failed for p3", dll_insert(l, p3, -1) == DLL_SUCCESS);
    mu_assert("dll_num_elements incorrect after inserts", dll_num_elements(l) == 3);

    // Test traversal and retrieval
    dll_node *node;
    int count = 0;
    dll_traverse(l, node) {
        person_t *current_person = (person_t *)node->data;
        mu_assert("Traversal failed: invalid data", current_person != NULL);
        if (count == 0) {
            mu_assert("Traversal failed: wrong person data (ID 1)", strcmp(current_person->name, "Alice") == 0 && current_person->id == 1);
        } else if (count == 1) {
            mu_assert("Traversal failed: wrong person data (ID 2)", strcmp(current_person->name, "Bob") == 0 && current_person->id == 2);
        } else if (count == 2) {
            mu_assert("Traversal failed: wrong person data (ID 3)", strcmp(current_person->name, "Charlie") == 0 && current_person->id == 3);
        }
        count++;
    }
    mu_assert("Traversal count mismatch", count == 3);

    // Test reverse traversal
    count = 0;
    dll_reverse_traverse(l, node) {
        person_t *current_person = (person_t *)node->data;
        mu_assert("Reverse traversal failed: invalid data", current_person != NULL);
        if (count == 0) {
            mu_assert("Reverse traversal failed: wrong person data (ID 3)", strcmp(current_person->name, "Charlie") == 0 && current_person->id == 3);
        } else if (count == 1) {
            mu_assert("Reverse traversal failed: wrong person data (ID 2)", strcmp(current_person->name, "Bob") == 0 && current_person->id == 2);
        } else if (count == 2) {
            mu_assert("Reverse traversal failed: wrong person data (ID 1)", strcmp(current_person->name, "Alice") == 0 && current_person->id == 1);
        }
        count++;
    }
    mu_assert("Reverse traversal count mismatch", count == 3);

    // Test dll_search by ID
    int search_id_bob = 2;
    dll_node *found_node_id = dll_search(l, &search_id_bob, find_person_by_id);
    mu_assert("dll_search failed for Bob by ID", found_node_id != NULL);
    mu_assert("dll_search returned wrong person by ID", ((person_t *)found_node_id->data)->id == 2);

    // Test dll_search by Name
    char *search_name_charlie = "Charlie";
    dll_node *found_node_name = dll_search(l, search_name_charlie, find_person_by_name);
    mu_assert("dll_search failed for Charlie by Name", found_node_name != NULL);
    mu_assert("dll_search returned wrong person by Name", strcmp(((person_t *)found_node_name->data)->name, "Charlie") == 0);

    // Test searching for a non-existent element
    int search_id_nonexistent = 99;
    mu_assert("dll_search found non-existent ID", dll_search(l, &search_id_nonexistent, find_person_by_id) == NULL);
    char *search_name_nonexistent = "David";
    mu_assert("dll_search found non-existent Name", dll_search(l, search_name_nonexistent, find_person_by_name) == NULL);


    // Test removal from the beginning
    person_t *removed_p1 = (person_t *)dll_remove(l, 0);
    mu_assert("dll_remove from front failed", removed_p1 != NULL && removed_p1->id == 1 && strcmp(removed_p1->name, "Alice") == 0);
    mu_assert("dll_num_elements incorrect after front removal", dll_num_elements(l) == 2);
    free(removed_p1); // Free the data

    // Test removal from the end
    person_t *removed_p3 = (person_t *)dll_remove(l, -1); // -1 for end
    mu_assert("dll_remove from end failed", removed_p3 != NULL && removed_p3->id == 3 && strcmp(removed_p3->name, "Charlie") == 0);
    mu_assert("dll_num_elements incorrect after end removal", dll_num_elements(l) == 1);
    free(removed_p3);

    // Test removal from middle (Bob is now at index 0)
    person_t *removed_p2 = (person_t *)dll_remove(l, 0);
    mu_assert("dll_remove from middle failed", removed_p2 != NULL && removed_p2->id == 2 && strcmp(removed_p2->name, "Bob") == 0);
    mu_assert("dll_num_elements incorrect after middle removal", dll_num_elements(l) == 0);
    free(removed_p2);

    // Test removing from an empty list
    mu_assert("dll_remove on empty list did not return NULL", dll_remove(l, 0) == NULL);

    dll_free(l); // Free the list structure itself (and nodes)
    // Note: dll_free does NOT free the data pointers unless a custom free function is provided,
    // which is not a feature of this basic example. We've freed manually above.

    return NULL;
}

// Minunit runner for dllist tests
char *(*all_tests[])() = {
    test_dllist_basic_ops,
    NULL
};

int main() {
    // If dll_init requires a comparator function and it's not implicitly handled,
    // this example might need adjustments. Assuming basic void* data and comparison via callbacks.
    return run_all_tests(all_tests);
}
