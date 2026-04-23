/*******************************************************************************
*   Demonstrate some of the uses of the doubly linked list datastructure by
*   adding people into a list. We will make a person struct to show it being
*   used with a non-standard datatype.
*
*   Use -v to include more debugging information
*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h> // For assert

#include "../src/dllist.h" // Assuming dllist.h is the header for doubly linked list


// Define a sample struct to store in the list
typedef struct person {
	int age;
	char gender;
	int height;    /* feet */
	int id;        /* order of getting here; for testing */
	char name[50]; /* Example string data */
} person_t;

// Helper function to create a new person
person_t*
create_person(int id, const char* name, int age, char gender, int height)
{
	person_t* p = (person_t*) malloc(sizeof(person_t));
	if (!p) {
		fprintf(stderr, "Error: Memory allocation failed for person.
");
		return NULL;
	}
	p->id = id;
	p->age = age;
	p->gender = gender;
	p->height = height;
	strncpy(p->name, name, sizeof(p->name) - 1);
	p->name[sizeof(p->name) - 1] = '\0'; // Ensure null termination
	return p;
}

// Callback function for dll_search to find a person by ID
bool find_person_by_id(void* data, void* key)
{
	person_t* p = (person_t*) data;
	int* id_to_find = (int*) key;
	return p != NULL && p->id == *id_to_find;
}

// Callback function for dll_search to find a person by name
bool find_person_by_name(void* data, void* key)
{
	person_t* p = (person_t*) data;
	char* name_to_find = (char*) key;
	return p != NULL && strcmp(p->name, name_to_find) == 0;
}

// Function to test basic dllist operations
void test_dllist_basic_operations()
{
	printf("--- Doubly Linked List Operations Example ---
");
	dllist_t l = dll_init();
	assert(l != NULL);
	printf("Doubly linked list initialized.
");

	// Test insertion at the end
	person_t* p1 = create_person(1, "Alice", 30, 'f', 5);
	person_t* p2 = create_person(2, "Bob", 25, 'm', 6);
	person_t* p3 = create_person(3, "Charlie", 35, 'm', 5);

	assert(dll_insert(l, p1, -1) == DLL_SUCCESS);
	assert(dll_insert(l, p2, -1) == DLL_SUCCESS);
	assert(dll_insert(l, p3, -1) == DLL_SUCCESS);
	assert(dll_num_elements(l) == 3);
	printf("Inserted 3 persons: Alice, Bob, Charlie.
");

	// Test traversal and retrieval
	printf("Traversing list forward:
");
	dll_node* node;
	int count = 0;
	dll_traverse(l, node)
	{
		person_t* current_person = (person_t*) node->data;
		assert(current_person != NULL);
		if (count == 0) {
			assert(strcmp(current_person->name, "Alice") == 0 && current_person->id == 1);
			printf("  - %d: %s (Age: %d)
", current_person->id, current_person->name, current_person->age);
		} else if (count == 1) {
			assert(strcmp(current_person->name, "Bob") == 0 && current_person->id == 2);
			printf("  - %d: %s (Age: %d)
", current_person->id, current_person->name, current_person->age);
		} else if (count == 2) {
			assert(strcmp(current_person->name, "Charlie") == 0 && current_person->id == 3);
			printf("  - %d: %s (Age: %d)
", current_person->id, current_person->name, current_person->age);
		}
		count++;
	}
	assert(count == 3);

	// Test reverse traversal
	printf("Traversing list backward:
");
	count = 0;
	dll_reverse_traverse(l, node)
	{
		person_t* current_person = (person_t*) node->data;
		assert(current_person != NULL);
		if (count == 0) {
			assert(strcmp(current_person->name, "Charlie") == 0 && current_person->id == 3);
			printf("  - %d: %s (Age: %d)
", current_person->id, current_person->name, current_person->age);
		} else if (count == 1) {
			assert(strcmp(current_person->name, "Bob") == 0 && current_person->id == 2);
			printf("  - %d: %s (Age: %d)
", current_person->id, current_person->name, current_person->age);
		} else if (count == 2) {
			assert(strcmp(current_person->name, "Alice") == 0 && current_person->id == 1);
			printf("  - %d: %s (Age: %d)
", current_person->id, current_person->name, current_person->age);
		}
		count++;
	}
	assert(count == 3);

	// Test dll_search by ID
	int search_id_bob = 2;
	dll_node* found_node_id = dll_search(l, &search_id_bob, find_person_by_id);
	assert(found_node_id != NULL);
	assert(((person_t*) found_node_id->data)->id == 2);
	printf("Found Bob by ID %d.
", search_id_bob);

	// Test dll_search by Name
	char* search_name_charlie = "Charlie";
	dll_node* found_node_name = dll_search(l, search_name_charlie, find_person_by_name);
	assert(found_node_name != NULL);
	assert(strcmp(((person_t*) found_node_name->data)->name, "Charlie") == 0);
	printf("Found Charlie by name "%s".
", search_name_charlie);

	// Test searching for a non-existent element
	int search_id_nonexistent = 99;
	assert(dll_search(l, &search_id_nonexistent, find_person_by_id) == NULL);
	char* search_name_nonexistent = "David";
	assert(dll_search(l, search_name_nonexistent, find_person_by_name) == NULL);
	printf("Verified non-existent entries not found.
");

	// Test removal from the beginning
	person_t* removed_p1 = (person_t*) dll_remove(l, 0);
	assert(removed_p1 != NULL && removed_p1->id == 1 && strcmp(removed_p1->name, "Alice") == 0);
	assert(dll_num_elements(l) == 2);
	printf("Removed Alice (ID: %d) from the beginning.
", removed_p1->id);
	free(removed_p1); // Free the data

	// Test removal from the end
	person_t* removed_p3 = (person_t*) dll_remove(l, -1); // -1 for end
	assert(removed_p3 != NULL && removed_p3->id == 3 && strcmp(removed_p3->name, "Charlie") == 0);
	assert(dll_num_elements(l) == 1);
	printf("Removed Charlie (ID: %d) from the end.
", removed_p3->id);
	free(removed_p3);

	// Test removal from middle (Bob is now at index 0)
	person_t* removed_p2 = (person_t*) dll_remove(l, 0);
	assert(removed_p2 != NULL && removed_p2->id == 2 && strcmp(removed_p2->name, "Bob") == 0);
	assert(dll_num_elements(l) == 0);
	printf("Removed Bob (ID: %d) from the middle.
", removed_p2->id);
	free(removed_p2);

	// Test removing from an empty list
	assert(dll_remove(l, 0) == NULL);
	printf("Verified removing from empty list returns NULL.
");

	// Free the list structure itself (nodes are freed, but not the data pointers)
	dll_free(l);
	printf("Doubly linked list structure freed.
");
	printf("--- Doubly Linked List Operations Example Finished ---
");
}

int main()
{
	test_dllist_basic_operations();
	return 0;
}
