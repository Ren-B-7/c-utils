#include <stdio.h>

#include "../src/bloom.h"

int main(void)
{
	BloomFilter bf;

	/* Initialize bloom filter
	   - estimated elements: 1000
	   - false positive rate: 1% (0.01)
	*/
	if (bloom_filter_init(&bf, 1000, 0.01) != BLOOM_SUCCESS) {
		fprintf(stderr, "Failed to initialize bloom filter\n");
		return 1;
	}

	/* Add some strings */
	bloom_filter_add_string(&bf, "hello");
	bloom_filter_add_string(&bf, "world");
	bloom_filter_add_string(&bf, "bloom");
	bloom_filter_add_string(&bf, "filter");

	/* Check membership */
	const char* tests[] = {"hello", "world", "foo", "bar", "bloom", NULL};

	for (int i = 0; tests[i] != NULL; i++) {
		int exists = bloom_filter_check_string(&bf, tests[i]);

		if (exists) {
			printf("'%s' is possibly in the set\n", tests[i]);
		} else {
			printf("'%s' is definitely NOT in the set\n", tests[i]);
		}
	}

	/* Print stats */
	printf("\n--- Bloom Filter Stats ---\n");
	bloom_filter_stats(&bf);

	printf("Current false positive rate: %f\n",
	 bloom_filter_current_false_positive_rate(&bf));

	printf("Elements added: %lu\n", bf.elements_added);

	/* Clean up */
	if (bloom_filter_destroy(&bf) != BLOOM_SUCCESS) {
		fprintf(stderr, "Failed to destroy bloom filter\n");
		return 1;
	}

	return 0;
}
