#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/set.h"

int main()
{
	SimpleSet my_set;
	const char* element1 = "apple";

	if (set_init_alt(&my_set, 4, NULL) == SET_MALLOC_ERROR) {
		fprintf(stderr, "Error: Failed to initialize set.");
		return 1;
	}

	set_add_str(&my_set, element1);
	set_contains_str(&my_set, element1);
	set_remove_str(&my_set, element1);

	set_destroy(&my_set);
	printf("Set operations completed.");

	return 0;
}
